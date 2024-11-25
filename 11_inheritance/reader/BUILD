load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "reader",
    hdrs = [
        "reader.h",
        "readers_util.h",
    ],
)

cc_test(
    name = "test_reader",
    size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":reader",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
        "//tools/util",
    ],
)
