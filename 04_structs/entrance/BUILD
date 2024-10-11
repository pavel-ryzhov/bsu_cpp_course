load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "entrance",
    hdrs = ["entrance.h"],
)

cc_test(
    name = "test_entrance",
    # size = "small",
    srcs = ["test_entrance.cpp"],
    deps = [
        ":entrance",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

filegroup(
    name = "files",
    srcs = glob([".data/*",]),
    tags = ["input_files"],
)

cc_test_if_exists(
    name = "private_tests",
    # size = "small",
    srcs = [".private_test.cpp"],
    data = ["files"],
    deps = [
        ":entrance",
        "//tools/util",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

