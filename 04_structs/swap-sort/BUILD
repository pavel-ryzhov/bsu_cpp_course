load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "swap_sort",
    hdrs = ["swap_sort.h"],
)

cc_test(
    name = "test_swap_sort",
    # size = "small",
    srcs = ["test_swap_sort.cpp"],
    deps = [
        ":swap_sort",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
