load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "t_partition",
    hdrs = ["partition.h"],
)

cc_test(
    name = "test_t_partition",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":t_partition",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
        "//tools/util",
    ],
)
