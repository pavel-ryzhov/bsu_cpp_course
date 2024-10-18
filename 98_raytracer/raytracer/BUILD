load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "options",
    hdrs = [
        "options/camera_options.h",
        "options/render_options.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//98_raytracer/raytracer-geom:geometry",
    ],
)

cc_library(
    name = "raytracer",
    hdrs = ["raytracer.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":options",
        "//98_raytracer/raytracer-reader:reader",
        "//tools/util:image_tools",
    ],
)

cc_library(
    name = "test_tools",
    hdrs = [
        "tests/commons.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":options",
        ":raytracer",
        "//tools/util",
        "//tools/util:image_tools",
        "@catch2",
    ],
)

filegroup(
    name = "files",
    srcs = glob(["tests/**/**"]),
    tags = ["input_files"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "test_raytracer_asan",
    srcs = ["test_asan.cpp"],
    data = ["files"],
    deps = [
        ":options",
        ":raytracer",
        ":test_tools",
        "//tools/util",
        "//tools/util:image_tools",
        "@catch2",
        "@catch2//:catch2_main",
    ],
)

cc_test(
    name = "test_raytracer_release",
    srcs = [
        "test_release.cpp",
    ],
    data = ["files"],
    tags = [
        "no_asan",
    ],
    deps = [
        ":options",
        ":raytracer",
        ":test_tools",
        "//tools/util",
        "//tools/util:image_tools",
        "@catch2",
        "@catch2//:catch2_main",
    ],
)
