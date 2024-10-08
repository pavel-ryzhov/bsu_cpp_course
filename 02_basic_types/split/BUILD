load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "split",
    hdrs = ["split.h"],
)

cc_test(
    name = "test_split",
    # size = "small",
    srcs = ["test_split.cpp"],
    deps = [
        ":split",
        "//tools/bazel:catch2",
    ],
)
