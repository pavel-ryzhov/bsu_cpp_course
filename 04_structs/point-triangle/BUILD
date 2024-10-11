load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "point_triangle",
    hdrs = ["point_triangle.h"],
)

cc_test(
    name = "test_point_triangle",
    # size = "small",
    srcs = ["test_point_triangle.cpp"],
    deps = [
        ":point_triangle",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":point_triangle",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
