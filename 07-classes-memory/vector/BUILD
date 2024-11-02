load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "vector",
    hdrs = ["vector.h"],
)

cc_test(
    name = "test_vector",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":vector",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
