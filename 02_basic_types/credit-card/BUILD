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
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
