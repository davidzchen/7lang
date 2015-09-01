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
  lua_State* lua = luaL_newstate();
  luaL_openlibs(lua);

  // Register midi_send function with Lua and store it in the midi_send
  // variable.
  lua_pushcfunction(lua, midi_send);
  lua_setglobal(lua, "midi_send");

  // Run the provided Lua file.
  if (luaL_dofile(lua, argv[1]) != 0) {
    // Exercise(medium, 2): Report any error information returned from the Lua
    // interpreter.
    std::cerr << "Error playing " << argv[1] << ": "
              << lua_tostring(lua, -1) << std::endl;
  }

  // Close the Lua API.
  lua_close(lua);
  return 0;
}
