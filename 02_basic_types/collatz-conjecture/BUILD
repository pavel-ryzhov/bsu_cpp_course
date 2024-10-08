load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "collatz_conjecture",
    hdrs = ["collatz_conjecture.h"],
)

cc_test(
    name = "test_collatz_conjecture",
    # size = "small",
    srcs = ["test_collatz_conjecture.cpp"],
    deps = [
        ":collatz_conjecture",
        "//tools/bazel:catch2",
    ],
)
