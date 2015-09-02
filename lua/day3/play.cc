#include <iostream>
#include <cstdint>
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

// C++ Wrapper for the Lua API.
class Lua {
 public:
  Lua() {}

  // Initializes the Lua API.
  bool Init() {
    lua_ = luaL_newstate();
    if (lua_ == nullptr) {
      return false;
    }
    luaL_openlibs(lua_);
    return true;
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
    if (luaL_dofile(lua_, file_name) != 0) {
      last_error_ = lua_tostring(lua_, -1);
      return false;
    }
    return true;
  }

  // Returns the last error pushed by Lua.
  const std::string GetError() {
    return std::string(last_error_);
  }

  // Closes the Lua API.
  void Close() {
    if (lua_ != nullptr) {
      lua_close(lua_);
    }
  }

 private:
  lua_State* lua_;
  const char* last_error_;
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
