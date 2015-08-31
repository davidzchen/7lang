package(default_visibility = ["//visibility:public"])

DIR_PREFIX = "lua-5.3.1"

cc_library(
    name = "lua-lib",
    srcs = [
        # Core language
        DIR_PREFIX + "/src/lapi.c",
        DIR_PREFIX + "/src/lcode.c",
        DIR_PREFIX + "/src/lctype.c",
        DIR_PREFIX + "/src/ldebug.c",
        DIR_PREFIX + "/src/ldo.c",
        DIR_PREFIX + "/src/ldump.c",
        DIR_PREFIX + "/src/lfunc.c",
        DIR_PREFIX + "/src/lgc.c",
        DIR_PREFIX + "/src/llex.c",
        DIR_PREFIX + "/src/lmem.c",
        DIR_PREFIX + "/src/lobject.c",
        DIR_PREFIX + "/src/lopcodes.c",
        DIR_PREFIX + "/src/lparser.c",
        DIR_PREFIX + "/src/lstate.c",
        DIR_PREFIX + "/src/lstring.c",
        DIR_PREFIX + "/src/ltable.c",
        DIR_PREFIX + "/src/ltm.c",
        DIR_PREFIX + "/src/lundump.c",
        DIR_PREFIX + "/src/lvm.c",
        DIR_PREFIX + "/src/lzio.c",

        # Standard libraries
        DIR_PREFIX + "/src/lauxlib.c",
        DIR_PREFIX + "/src/lbaselib.c",
        DIR_PREFIX + "/src/lbitlib.c",
        DIR_PREFIX + "/src/lcorolib.c",
        DIR_PREFIX + "/src/ldblib.c",
        DIR_PREFIX + "/src/liolib.c",
        DIR_PREFIX + "/src/lmathlib.c",
        DIR_PREFIX + "/src/loslib.c",
        DIR_PREFIX + "/src/lstrlib.c",
        DIR_PREFIX + "/src/ltablib.c",
        DIR_PREFIX + "/src/lutf8lib.c",
        DIR_PREFIX + "/src/loadlib.c",
        DIR_PREFIX + "/src/linit.c",
    ],
    hdrs = [
        DIR_PREFIX + "/src/lua.h",
        DIR_PREFIX + "/src/luaconf.h",
        DIR_PREFIX + "/src/lualib.h",
        DIR_PREFIX + "/src/lauxlib.h",
    ],
    defines = ["LUA_USE_LINUX"],
    includes = [DIR_PREFIX + "/src"],
    linkopts = [
        "-lm",
        "-ldl",
    ],
    nocopts = "-fno-exceptions",
)

cc_binary(
    name = "lua",
    srcs = [DIR_PREFIX + "/src/lua.c"],
    deps = [":lua-lib"],
)

cc_binary(
    name = "luac",
    srcs = [DIR_PREFIX + "/src/luac.c"],
    deps = [":lua-lib"],
)
