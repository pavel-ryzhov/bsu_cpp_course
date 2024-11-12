load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "smart_ptr",
    hdrs = ["smart_ptr.h"],
)

cc_test(
    name = "test_smart_ptr",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":smart_ptr",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
