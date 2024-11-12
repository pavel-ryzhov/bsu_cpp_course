load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "deque",
    hdrs = ["deque.h"],
)

cc_test(
    name = "test_deque",
    # size = "small",
    timeout = "short",
    srcs = ["test.cpp"],
    deps = [
        ":deque",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
        "//tools/util",
    ],
)
