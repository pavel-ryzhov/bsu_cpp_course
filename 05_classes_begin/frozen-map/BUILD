load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "frozen_map",
    hdrs = ["frozen_map.h"],
)

cc_test(
    name = "test_frozen_map",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":frozen_map",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
