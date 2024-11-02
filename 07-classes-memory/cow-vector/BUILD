load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "cow_vector",
    hdrs = ["cow_vector.h"],
)

cc_test(
    name = "test_cow",
    size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":cow_vector",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
