load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "unique",
    hdrs = ["unique.h"],
)

cc_test(
    name = "test_unique",
    # size = "small",
    srcs = ["test_unique.cpp"],
    deps = [
        ":unique",
        "//tools/bazel:catch2",
    ],
)
