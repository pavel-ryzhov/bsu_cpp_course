load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "quadratic",
    hdrs = ["quadratic.h"],
)

cc_test(
    name = "test_quadratic",
    # size = "small",
    srcs = ["test_quadratic.cpp"],
    deps = [
        ":quadratic",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
