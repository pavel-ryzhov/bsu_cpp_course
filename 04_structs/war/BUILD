load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "war",
    hdrs = ["war.h"],
)

cc_test(
    name = "test_war",
    # size = "small",
    srcs = ["test_war.cpp"],
    deps = [
        ":war",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
