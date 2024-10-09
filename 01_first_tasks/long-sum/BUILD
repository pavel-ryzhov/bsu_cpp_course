load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "long_sum",
    hdrs = ["long_sum.h"],
)

cc_test(
    name = "test_long_sum",
    # size = "small",
    srcs = ["test_long_sum.cpp"],
    deps = [
        ":long_sum",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":long_sum",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
