load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "permutations",
    hdrs = ["permutations.h"],
)

cc_test(
    name = "test_permutations",
    # size = "small",
    srcs = ["test_permutations.cpp"],
    deps = [
        ":permutations",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
