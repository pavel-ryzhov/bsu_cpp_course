load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "accurate_sum",
    hdrs = ["accurate_sum.h"],
)

cc_test(
    name = "test_accurate_sum",
    # size = "small",
    srcs = ["test_accurate_sum.cpp"],
    deps = [
        ":accurate_sum",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "test_private_accurate_sum",
    # size = "small",
    srcs = [".accurate_sum_test.cpp"],
    deps = [
        ":accurate_sum",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
