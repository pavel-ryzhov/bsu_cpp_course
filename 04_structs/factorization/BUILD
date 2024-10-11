load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//tools/bazel:helpers.bzl", "cc_test_if_exists")

cc_library(
    name = "factorization",
    hdrs = ["factorization.h"],
)

cc_test(
    name = "test_factorization",
    # size = "small",
    srcs = ["test_factorization.cpp"],
    deps = [
        ":factorization",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
