load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "dungeon",
    hdrs = [
        "dungeon.h",
        "rogue.h",
    ],
)

cc_test(
    name = "test_dungeon",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":dungeon",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
        "//tools/util",
    ],
)
