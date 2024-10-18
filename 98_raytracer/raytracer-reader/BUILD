load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "reader",
    hdrs = [
        "light.h",
        "material.h",
        "object.h",
        "scene.h",
    ],
    deps = [
        "//98_raytracer/raytracer-geom:geometry",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "files",
    srcs = glob(["tests/*",]),
    tags = ["input_files"],
)

cc_test(
    name = "test_reader",
    srcs = ["test.cpp"],
    data = ["files"],
    deps = [
        "//tools/util",
        ":reader",
        "//98_raytracer/raytracer-geom:geometry",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)
