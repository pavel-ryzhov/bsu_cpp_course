load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "word_count",
    hdrs = ["word_count.h"],
)

cc_test(
    name = "test_word_count",
    # size = "small",
    srcs = ["test_word_count.cpp"],
    deps = [
        ":word_count",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
