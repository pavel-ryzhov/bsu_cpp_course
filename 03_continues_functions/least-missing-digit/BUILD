load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "least_missing_digit",
    hdrs = ["least_missing_digit.h"],
)

cc_test(
    name = "test_least_missing_digit",
    # size = "small",
    srcs = ["test_least_missing_digit.cpp"],
    deps = [
        ":least_missing_digit",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":least_missing_digit",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
