Lua Day 3: Lua and the World
============================

Making music with Lua.

Background
----------

The book uses Cmake to build the C++ code. We are using [Bazel][http://bazel.io]
instead.

This solution does not require you to have Lua or RtMidi installed on your
system. Instead, it uses Bazel's workspace rules to fetch these dependencies
and build them. For more information, see the following relevant files (relative
to the root of the source tree):

* `WORKSPACE`
* `lua/day3/rtmidi.BUILD`
* `tools/build_defs/lua/lua.BUILD`

How to build
------------

First, [install Bazel](http://bazel.io/docs/install.html).

To build `play`:

```sh
bazel build //lua/day3:play
```

Playing music
-------------

To play the music under `/lua/day3`, open your synthesizer and then run
`play`:

```sh
cd lua/day3
../../bazel-bin/lua/day3/play canon.lua
../../bazel-bin/lua/day3/play good_morning_to_all.lua
```
