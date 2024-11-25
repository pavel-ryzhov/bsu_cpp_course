load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "small_test_framework",
    hdrs = ["small_test_framework.h"],
)

cc_test(
    name = "test_small_test_framework",
    size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":small_test_framework",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
