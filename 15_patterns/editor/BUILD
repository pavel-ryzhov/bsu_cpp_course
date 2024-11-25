load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "editor",
    hdrs = ["editor.h"],
)

cc_test(
    name = "test_editor",
    size = "small",
    srcs = ["test.cpp"],
    data = ["test_data"],
    deps = [
        ":editor",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
        "//tools/util",
    ],
)

filegroup(
    name = "test_data",
    srcs = [
        "random.txt",
    ],
)
