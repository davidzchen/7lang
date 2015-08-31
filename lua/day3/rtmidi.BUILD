package(default_visibility = ["//visibility:public"])

config_setting(
    name = "darwin",
    values = {"host_cpu": "darwin"},
)

config_setting(
    name = "k8",
    values = {"host_cpu": "k8"},
)

cc_library(
    name = "rtmidi",
    srcs = ["RtMidi.cpp"],
    hdrs = ["RtMidi.h"],
    copts = select({
        ":darwin": ["-D__MACOSX_CORE__"],
        ":k8": ["-D__LINUX_ALSA__"],
    }),
    linkopts = select({
        ":darwin": [
            "-framework CoreMIDI",
            "-framework CoreAudio",
            "-framework CoreFoundation",
        ],
        ":k8": [
            "-lasound",
            "-lpthread",
        ],
    }),
)
