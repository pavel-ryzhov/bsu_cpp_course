load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "pimpl",
    srcs = ["ugly.cpp"],
    hdrs = [
        "bad.h",
        "ugly.h",
    ],
)

cc_test(
    name = "test_pimpl",
    size = "small",
    srcs = ["good.cpp"],
    deps = [
        ":pimpl",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
         "//tools/util",
    ],
)
