load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "bin_pow",
    hdrs = ["bin_pow.h"],
)

cc_test(
    name = "test_bin_pow",
    # size = "small",
    srcs = ["test_bin_pow.cpp"],
    deps = [
        ":bin_pow",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
