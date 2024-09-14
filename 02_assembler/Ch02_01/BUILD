load("//tools/bazel:nasm_library.bzl", "nasm_library")
load("@rules_cc//cc:defs.bzl", "cc_binary")

nasm_library(
    name = "nasm_add_sub",
    srcs = [
        "Ch02_01_fasm.s",
    ],
    hdrs = [
        "ModX86Asm3eNASM.inc",
    ],
    tags = [
        "no_clang_tidy",
        "no_clang_format",
    ],
)

cc_binary(
    name = "add_sub",
    srcs = [
        "Ch02_01.cpp",
        "Ch02_01.h",
        "Ch02_01_misc.cpp",
        ":nasm_add_sub",
    ],
    copts = [
        "-m64",
        "-mavx",
    ],
    tags = [
        "no_clang_tidy",
        "no_clang_format",
    ],
)
