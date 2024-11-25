load("@rules_cc//cc:defs.bzl", "cc_binary")

filegroup(
    name = "files",
    srcs = ["input.txt"],
    tags = ["input_files"],
)

cc_binary(
    name = "gcd",
    srcs = ["gcd.cpp"],
    data = ["files"],
)
