load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "dedup",
    hdrs = ["dedup.h"],
)

cc_test(
    name = "test_dedup",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":dedup",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
