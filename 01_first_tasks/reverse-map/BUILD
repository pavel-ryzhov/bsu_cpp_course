load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "reverse_map",
    hdrs = ["reverse_map.h"],
)

cc_test(
    name = "test_reverse_map",
    # size = "small",
    srcs = ["test_reverse_map.cpp"],
    deps = [
        ":reverse_map",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
