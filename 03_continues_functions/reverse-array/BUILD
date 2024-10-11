load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "reverse_array",
    hdrs = ["reverse_array.h"],
)

cc_test(
    name = "test_reverse_array",
    # size = "small",
    srcs = ["test_reverse_array.cpp"],
    deps = [
        ":reverse_array",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":reverse_array",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
