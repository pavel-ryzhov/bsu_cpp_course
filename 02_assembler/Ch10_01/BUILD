load("//tools/bazel:nasm_library.bzl", "nasm_library")
load("@rules_cc//cc:defs.bzl", "cc_binary")

nasm_library(
    name = "nasm_arithmetic_avx2",
    srcs = [
        "Ch10_01_fasm.s",
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
    name = "arithmetic_avx2",
    srcs = [
        "Ch10_01.cpp",
        "Ch10_01.h",
        "YmmVal.h",
        ":nasm_arithmetic_avx2",
    ],
    copts = [
        "-m64",
        "-mavx2",
    ],
    tags = [
        "no_clang_tidy",
        "no_clang_format",
    ],
)
