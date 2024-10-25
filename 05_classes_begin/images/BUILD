load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "images",
    hdrs = [
        "image.h",
        "matrix.h",
    ],
    deps = [
        "//tools/util:image_tools",
    ],
)

cc_library(
    name = "helpers",
    srcs = [
        "helpers/image_io.cc",
    ],
    hdrs = [
        "helpers/image_io.h",
    ],
    deps = [
        ":images",
    ],
)

filegroup(
    name = "files",
    srcs = glob(["static/**"]),
    tags = ["input_files"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "images_demo",
    srcs = [
        "demo.cpp",
    ],
    data = ["files"],
    deps = [
        ":helpers",
        ":images",
        "//tools/util",
        "//tools/util:image_tools",
    ],
)

cc_test(
    name = "test_image",
    # size = "small",
    srcs = ["test_image.cpp"],
    deps = [
        ":images",
        "@catch2",
        "@catch2//:catch2_main",
    ],
)

cc_test(
    name = "test_matrix",
    # size = "small",
    srcs = ["test_matrix.cpp"],
    deps = [
        ":images",
        "@catch2",
        "@catch2//:catch2_main",
    ],
)

cc_test(
    name = "test_bonus",
    # size = "small",
    srcs = ["test_matrix.cpp"],
    deps = [
        ":images",
        "@catch2",
        "@catch2//:catch2_main",
    ],
)
