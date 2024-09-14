load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test_rop",
    srcs = [
        "rop.S",
        "rop.h",
        "ropchain.c",
        "test.c",
    ],
    copts = [
        "-no-pie",
    ],
    linkopts = [
        "-no-pie",
        "-O2",
        "-fno-omit-frame-pointer",
        "-fno-PIC",
        "-fno-pie",
    ],
    tags = [
        "no_clang_tidy",
        "no_clang_format",
        "no_asan",
    ],
)
