load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "itertools",
    hdrs = ["itertools.h"],
)

cc_test(
    name = "test_itertools",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":itertools",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
