load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "lru_cache",
    hdrs = ["lru_cache.h"],
)

cc_test(
    name = "test_lru_cache",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":lru_cache",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
        "//tools/util",
    ],
)
