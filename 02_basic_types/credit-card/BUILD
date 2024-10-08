load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "credit_card",
    hdrs = ["credit_card.h"],
)

cc_test(
    name = "test_credit_card",
    # size = "small",
    srcs = ["test_credit_card.cpp"],
    deps = [
        ":credit_card",
        "//tools/bazel:catch2",
    ],
)
