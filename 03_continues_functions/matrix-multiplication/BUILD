load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "matrix_multiplication",
    hdrs = ["matrix_multiplication.h"],
)

cc_test(
    name = "test_matrix_multiplication",
    # size = "small",
    srcs = ["test_matrix_multiplication.cpp"],
    deps = [
        ":matrix_multiplication",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":matrix_multiplication",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
