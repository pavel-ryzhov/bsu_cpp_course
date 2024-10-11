load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "sort_students",
    hdrs = ["sort_students.h"],
)

cc_test(
    name = "test_sort_students",
    # size = "small",
    srcs = ["test_sort_students.cpp"],
    deps = [
        ":sort_students",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":sort_students",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
