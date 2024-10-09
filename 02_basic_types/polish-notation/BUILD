load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "polish_notation",
    hdrs = ["polish_notation.h"],
)

cc_test(
    name = "test_polish_notation",
    # size = "small",
    srcs = ["test_polish_notation.cpp"],
    deps = [
        ":polish_notation",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
