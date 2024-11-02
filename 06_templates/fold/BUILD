load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "fold",
    hdrs = ["fold.h"],
)

cc_test(
    name = "test_fold",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":fold",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
        "//tools/util",
    ],
)
