load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "stack",
    hdrs = [
        "stack.h",
    ],
)

cc_test(
    name = "test_stack",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":stack",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
