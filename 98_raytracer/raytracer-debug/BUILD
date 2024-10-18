load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

filegroup(
    name = "files",
    srcs = glob(["tests/**/**",]),
    tags = ["input_files"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "test_raytracer_asan",
    srcs = ["test_asan.cpp"],
    data = ["files"],
    deps = [
        "//98_raytracer/raytracer:raytracer",
        "//98_raytracer/raytracer:options",
        "//98_raytracer/raytracer:test_tools",
        "//tools/util:image_tools",
        "//tools/util",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
)

cc_test(
    name = "test_raytracer_release",
    srcs = [
        "test_release.cpp",
    ],
    data = ["files"],
    deps = [
        "//98_raytracer/raytracer:raytracer",
        "//98_raytracer/raytracer:options",
        "//98_raytracer/raytracer:test_tools",
        "//tools/util:image_tools",
        "//tools/util",
        "@catch2//:catch2_main",
        "@catch2//:catch2",
    ],
    tags = [
        "no_asan",
    ],
)
