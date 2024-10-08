load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "fractal",
    hdrs = [
        "fractal.h",
        "function.h",
    ],
)

cc_test(
    name = "test_fractal",
    # size = "small",
    srcs = ["test_fractal.cpp"],
    deps = [
        ":fractal",
        "//tools/bazel:catch2",
    ],
)
