load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "calculator",
    hdrs = [
        "calculator.h",
        "eval.h",
    ],
)

cc_test(
    name = "test_calculator",
    size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":calculator",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
