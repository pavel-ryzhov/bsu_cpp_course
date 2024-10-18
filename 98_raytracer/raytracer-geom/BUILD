load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "geometry",
    hdrs = [
        "geometry.h",
        "intersection.h",
        "ray.h",
        "sphere.h",
        "triangle.h",
        "vector.h",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "files",
    srcs = glob(["tests/*",]),
    tags = ["input_files"],
)

cc_test(
    name = "test_geometry",
    srcs = ["test.cpp"],
    data = ["files"],
    deps = [
        "//tools/util",
        ":geometry",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
