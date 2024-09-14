load("//tools/bazel:nasm_library.bzl", "nasm_library")
load("@rules_cc//cc:defs.bzl", "cc_binary")

nasm_library(
    name = "nasm_arithmetic_avx512",
    srcs = [
        "Ch14_01_fasm.s",
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
    name = "arithmetic_avx512",
    srcs = [
        "Ch14_01.cpp",
        "Ch14_01.h",
        "ZmmVal.h",
        ":nasm_arithmetic_avx512",
    ],
    copts = [
        "-m64",
        # "-mavx",
        # "-mfma",
        # "-mavx512bw",
        # "-mavx512cd",
        # "-mavx512dq",
        "-mavx512f",
        # "-mprefer-vector-width=256",
        # "-mtune=generic",
        # "-mavx512vl",
        # "-mfma",
        # "-march=x86-64",
        "-march=native",
        # "-march=knl",
        # "-mtune=skylake-avx512",
        # "-march=skylake-avx512",
        # "-std=c++20",
    ],
    linkopts = [
        # "-m64",
        # "-mavx",
        # "-mfma",
        # "-mavx512bw",
        # "-mavx512cd",
        # "-mavx512dq",
        # "-mavx512f",
        # "-mavx512vl",
        # "-mfma",
        # "-mtune=skylake-avx512",
        # "-march=native",
        # "-march=knl",
        # "-march=x86-64-v4adfadsf",
        # "-march=skylake-avx512",
    ],
    linkstatic = True,
    tags = [
        "no_clang_tidy",
        "no_clang_format",
    ],
)
