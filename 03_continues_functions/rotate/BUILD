load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "rotate",
    hdrs = ["rotate.h"],
)

cc_test(
    name = "test_rotate",
    # size = "small",
    srcs = ["test_rotate.cpp"],
    deps = [
        ":rotate",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":rotate",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
