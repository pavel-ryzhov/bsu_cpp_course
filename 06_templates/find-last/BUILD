load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "find_last",
    hdrs = ["find_last.h"],
)

cc_test(
    name = "test_find_last",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":find_last",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
        "//tools/util",
    ],
)
