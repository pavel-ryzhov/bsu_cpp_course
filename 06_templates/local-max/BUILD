load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "local_max",
    hdrs = ["local_max.h"],
)

cc_test(
    name = "test_local_max",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":local_max",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    deps = [
        ":local_max",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
        "//tools/util",
    ],
)
