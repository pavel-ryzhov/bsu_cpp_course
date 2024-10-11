load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "permutation",
    hdrs = ["permutation.h"],
)

cc_test(
    name = "test_permutation",
    # size = "small",
    srcs = ["test_permutation.cpp"],
    deps = [
        ":permutation",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":permutation",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
