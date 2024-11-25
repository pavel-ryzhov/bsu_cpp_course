load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "any",
    hdrs = ["any.h"],
)

cc_test(
    name = "test_any",
    size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":any",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
