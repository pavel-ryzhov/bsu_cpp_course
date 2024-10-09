load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "diff_pairs",
    hdrs = ["diff_pairs.h"],
)

cc_test(
    name = "test_diff_pairs",
    # size = "small",
    srcs = ["test_diff_pairs.cpp"],
    deps = [
        ":diff_pairs",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":diff_pairs",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
