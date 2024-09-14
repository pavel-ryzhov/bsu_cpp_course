load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test_helloasm",
    srcs = [
        "asm.S",
        "test.S",
    ],
    copts = [
        "-no-pie",
        "-O2",
        "-fno-omit-frame-pointer",
        "-fno-PIC",
        "-fno-pie",
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
    ],
)
