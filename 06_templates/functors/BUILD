load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "functors",
    hdrs = ["functors.h"],
)

cc_test(
    name = "test_functors",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":functors",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":functors",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
