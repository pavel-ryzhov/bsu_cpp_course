load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "intrusive_list",
    hdrs = ["intrusive_list.h"],
)

cc_test(
    name = "test_intrusive_list",
    size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":intrusive_list",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
