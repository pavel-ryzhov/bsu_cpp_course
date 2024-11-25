load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "tryhard",
    hdrs = ["try.h"],
)

cc_test(
    name = "test_try",
    size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":tryhard",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
