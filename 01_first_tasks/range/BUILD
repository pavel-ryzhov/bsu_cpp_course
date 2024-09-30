load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "range",
    hdrs = ["range.h"],
)

cc_test(
    name = "test_range",
    # size = "small",
    srcs = ["test_range.cpp"],
    deps = [
        ":range",
        "//tools/bazel:catch2",
    ],
)
