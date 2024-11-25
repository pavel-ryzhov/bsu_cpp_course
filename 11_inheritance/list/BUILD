load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "list",
    hdrs = ["list.h"],
)

cc_test(
    name = "test_list",
    size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":list",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
