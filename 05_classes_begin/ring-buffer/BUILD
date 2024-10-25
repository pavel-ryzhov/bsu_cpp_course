load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "ring_buffer",
    hdrs = ["ring_buffer.h"],
)

cc_test(
    name = "test_ring_buffer",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":ring_buffer",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
