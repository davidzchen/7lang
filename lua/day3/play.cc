#include <iostream>
#include <cstdint>
#include <set>
#include <vector>

extern "C" {
#include "external/lua/lua-5.3.1/src/lua.h"
#include "external/lua/lua-5.3.1/src/lauxlib.h"
#include "external/lua/lua-5.3.1/src/lualib.h"
}
#include "external/rtmidi/RtMidi.h"

// Singleton class that wraps RtMidiOut.
//
// For simplicity, the book uses a global RtMidiOut variable. We use a singleton
// wrapper class instead.
class MidiOut {
 public:
  static MidiOut* Get() {
    if (instance_ == nullptr) {
      instance_ = new MidiOut();
    }
    return instance_;
  }

  bool Open(uint32_t port) {
    uint32_t ports = midi_.getPortCount();
    if (ports < 1) {
      std::cerr << "No ports available." << std::endl;
      return false;
    }
    midi_.openPort(port);
    return true;
  }

  void Send(uint8_t number, uint8_t note, uint8_t velocity) {
    std::vector<uint8_t> message{number, note, velocity};
    midi_.sendMessage(&message);
  }

 private:
  MidiOut() {}

  static MidiOut* instance_;

  RtMidiOut midi_;
};

MidiOut* MidiOut::instance_ = nullptr;

class LuaStates {
 public:
  static LuaStates* Get() {
    if (instance_ == nullptr) {
      instance_ = new LuaStates();
    }
    return instance_;
  }

  lua_State* Add() {
    lua_State* state = luaL_newstate();
    luaL_openlibs(state);
    if (state == nullptr) {
      return nullptr;
    }
    states_.insert(state);
    return state;
  }

  void ForEachState(std::function<void(lua_State* state)> cb) {
    for (lua_State* state : states_) {
      cb(state);
    }
  }

  void Close(lua_State* state) {
    lua_close(state);
  }

 private:
  LuaStates() {}

  static LuaStates* instance_;

  std::set<lua_State*> states_;
};

LuaStates* LuaStates::instance_ = nullptr;

static void LuaStop(lua_State* lua, lua_Debug* ar) {
  (void)ar;  // unused
  lua_sethook(lua, NULL, 0, 0);
  luaL_error(lua, "interrupted!");
}

static void LuaAction(int i) {
  // If another SIGINT happens before LuaStop, terminate process (default
  // action).
  signal(i, SIG_DFL);
  LuaStates::Get()->ForEachState([&](lua_State* state) {
    lua_sethook(state, LuaStop, LUA_MASKCALL | LUA_MASKRET | LUA_MASKCOUNT, 1);
  });
}

static int traceback(lua_State* lua) {
  const char* message = lua_tostring(lua, 1);
  if (message != nullptr) {
    luaL_traceback(lua, lua, message, 1);
  } else if (!lua_isnoneornil(lua, 1)) {
    // Is there an error object? Try its 'tostring' method.
    if (!luaL_callmeta(lua, 1, "__tostring")) {
      lua_pushliteral(lua, "(no error message)");
    }
  }
  return 1;
}

// C++ Wrapper for the Lua API.
class Lua {
 public:
  Lua() {}

  // Initializes the Lua API.
  bool Init() {
    lua_ = LuaStates::Get()->Add();
    return lua_ != nullptr;
  }

  // Registers a C function as a global Lua function.
  void PushCFunction(lua_CFunction function, const char* name) {
    if (lua_ == nullptr || name == nullptr) {
      return;
    }
    lua_pushcfunction(lua_, function);
    lua_setglobal(lua_, name);
  }

  // Runs the provided Lua file.
  bool DoFile(const char* file_name) {
    if (lua_ == nullptr || file_name == nullptr) {
      return false;
    }
    int status = luaL_dofile(lua_, file_name);
    if (status != 0) {
      ReportError(status);
      return false;
    }
    return true;
  }

  bool DoLibrary(const char* file_name) {
    if (lua_ == nullptr || file_name == nullptr) {
      return false;
    }
    lua_getglobal(lua_, "require");
    lua_pushstring(lua_, file_name);
    // Call `require(name)`
    int status = DoCall(1, 1);
    if (status != LUA_OK) {
      ReportError(status);
      return false;
    }
    // global[file_name] = require return
    lua_setglobal(lua_, file_name);
    return true;
  }

  // Returns the last error pushed by Lua.
  const std::string GetError() {
    return last_error_;
  }

  // Closes the Lua API.
  void Close() {
    if (lua_ != nullptr) {
      LuaStates::Get()->Close(lua_);
    }
  }

 private:
  void ReportError(int status) {
    if (status == LUA_OK || lua_isnil(lua_, -1)) {
      return;
    }
    const char* message = lua_tostring(lua_, -1);
    if (message == nullptr) {
      message = "(error object is not a string)";
    }
    last_error_ = std::string(message);
    lua_pop(lua_, 1);
    // Force a complete garbage collection in case of errors.
    lua_gc(lua_, LUA_GCCOLLECT, 0);
  }

  int DoCall(int narg, int nres) {
    // Function index.
    int base = lua_gettop(lua_) - narg;
    // Push traceback function
    lua_pushcfunction(lua_, traceback);
    // Put it under chunk and args
    lua_insert(lua_, base);
    signal(SIGINT, LuaAction);
    int status = lua_pcall(lua_, narg, nres, base);
    signal(SIGINT, SIG_DFL);
    // Remove traceback function.
    lua_remove(lua_, base);
    return status;
  }

  lua_State* lua_;
  std::string last_error_;
};

// Sends a MIDI note.
int midi_send(lua_State* lua) {
  double status = lua_tonumber(lua, -3);
  double data1 = lua_tonumber(lua, -2);
  double data2 = lua_tonumber(lua, -1);

  MidiOut::Get()->Send(static_cast<uint8_t>(status),
                       static_cast<uint8_t>(data1),
                       static_cast<uint8_t>(data2));
  return 0;
}

int main(int argc, const char** argv) {
  if (argc < 1) {
    std::cerr << "Usage: play SONG_FILE.lua" << std::endl;
    return -1;
  }

  // Find a running synthesizer.
  if (!MidiOut::Get()->Open(0)) {
    return -1;
  }

  // Initialize the Lua API.
  Lua lua;
  if (!lua.Init()) {
    std::cerr << "Error initializing Lua." << std::endl;
    return -1;
  }

  // Register midi_send function with Lua and store it in the midi_send
  // variable.
  lua.PushCFunction(midi_send, "midi_send");

  // Load the music notation library.
  if (!lua.DoLibrary("notation")) {
    std::cerr << "Error loading notation library: "
              << lua.GetError() << std::endl;
    return -1;
  }

  // Run the provided Lua file.
  if (!lua.DoFile(argv[1])) {
    // Exercise(medium, 2): Report any error information returned from the Lua
    // interpreter.
    std::cerr << "Error playing " << argv[1] << ": "
              << lua.GetError() << std::endl;
  }

  // Close the Lua API.
  lua.Close();
  return 0;
}
