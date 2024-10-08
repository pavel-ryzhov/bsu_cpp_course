load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "arithmetic_mean",
    hdrs = ["arithmetic_mean.h"],
)

cc_test(
    name = "test_arithmetic_mean",
    # size = "small",
    srcs = ["test_arithmetic_mean.cpp"],
    deps = [
        ":arithmetic_mean",
        "//tools/bazel:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":arithmetic_mean",
        "//tools/bazel:catch2",
        "//tools/util",
    ],
)
