load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "common_elements",
    hdrs = ["common_elements.h"],
)

cc_test(
    name = "test_common_elements",
    # size = "small",
    srcs = ["test_common_elements.cpp"],
    deps = [
        ":common_elements",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":common_elements",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
