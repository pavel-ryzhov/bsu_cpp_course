load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "safe_transform",
    hdrs = ["safe_transform.h"],
)

cc_test(
    name = "test_safe_transform",
    size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":safe_transform",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
