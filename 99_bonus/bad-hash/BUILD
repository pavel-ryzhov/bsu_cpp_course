load("@rules_cc//cc:defs.bzl", "cc_binary")

filegroup(
    name = "files",
    srcs = ["input.txt"],
    tags = ["input_files"],
)

cc_binary(
    name = "bad_hash",
    srcs = ["run.cpp"],
    data = ["files"],
    deps = [
        "//tools/util",
    ],
)
