#include <iostream>
#include <vector>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "RtMidi.h"

static RtMidiOut midi;

// Sends a MIDI note.
int midi_send(lua_State* lua) {
  double status = lua_tonumber(lua, -3);
  double data1 = lua_tonumber(lua, -2);
  double data2 = lua_tonumber(lua, -1);

  std::vector<unsigned char> message(3);
  message[0] = static_cast<unsigned char>(status);
  message[1] = static_cast<unsigned char>(data1);
  message[2] = static_cast<unsigned char>(data2);
  midi.sendMessage(&message);

  return 0;
}

int main(int argc, const char** argv) {
  if (argc < 1) {
    std::cerr << "Usage: play SONG_FILE.lua" << std::endl;
    return -1;
  }

  // Find a running synthesizer using the rtmidi API.
  unsigned int ports = midi.getPortCount();
  if (ports < 1) {
    std::cerr << "No ports available." << std::endl;
    return -1;
  }
  midi.openPort(0);

  // Initialize the Lua API.
  lua_State* lua = luaL_newstate();
  luaL_openlibs(lua);

  // Register midi_send function with Lua and store it in the midi_send
  // variable.
  lua_pushcfunction(lua, midi_send);
  lua_setglobal(lua, "midi_send");

  // Run the provided Lua file.
  luaL_dofile(lua, argv[1]);

  // Close the Lua API.
  lua_close(lua);
  return 0;
}
