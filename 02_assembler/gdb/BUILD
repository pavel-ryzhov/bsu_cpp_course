load("@rules_cc//cc:defs.bzl", "cc_binary")

filegroup(
    name = "files",
    srcs = ["input.txt", "a.out"],
    tags = ["input_files"],
)

sh_binary(
    name = "run_a",
    srcs = ["run.sh"],
    data = ["files"],
)
