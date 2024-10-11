load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "filter_array",
    hdrs = ["filter_array.h"],
)

cc_test(
    name = "test_filter_array",
    # size = "small",
    srcs = ["test_filter_array.cpp"],
    deps = [
        ":filter_array",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":filter_array",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
