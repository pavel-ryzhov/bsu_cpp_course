load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "context",
    srcs = [
        "context.S",
    ],
    hdrs = [
        "context.h",
    ],
    tags = [
        "no_clang_tidy",
        "no_clang_format",
    ],
)

cc_test(
    name = "test_context",
    size = "small",
    srcs = ["test.c"],
    copts = [
        "-no-pie",
        "-O2",
        "-fno-omit-frame-pointer",
    ],
    deps = [
        ":context",
    ],
    tags = [
        "no_clang_tidy",
        "no_clang_format",
    ],
)
