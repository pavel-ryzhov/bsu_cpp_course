load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "lib",
    hdrs = ["sum.h"],
)

cc_test(
    name = "public_tests",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":lib",
        "//tools/bazel:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":lib",
        "//tools/bazel:catch2",
    ],
)
