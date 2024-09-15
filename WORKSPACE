workspace(name = "bsu_cpp")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "io_bazel_rules_go",
    sha256 = "6dc2da7ab4cf5d7bfc7c949776b1b7c733f05e56edc4bcd9022bb249d2e2a996",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_go/releases/download/v0.39.1/rules_go-v0.39.1.zip",
        "https://github.com/bazelbuild/rules_go/releases/download/v0.39.1/rules_go-v0.39.1.zip",
    ],
)

load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")

go_rules_dependencies()

go_register_toolchains(version = "1.20.3")

http_archive(
    name = "bazel_gazelle",
    sha256 = "727f3e4edd96ea20c29e8c2ca9e8d2af724d8c7778e7923a854b2c80952bc405",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-gazelle/releases/download/v0.30.0/bazel-gazelle-v0.30.0.tar.gz",
        "https://github.com/bazelbuild/bazel-gazelle/releases/download/v0.30.0/bazel-gazelle-v0.30.0.tar.gz",
    ],
)

load("@bazel_gazelle//:deps.bzl", "gazelle_dependencies")

gazelle_dependencies()

http_archive(
    name = "com_google_protobuf",
    sha256 = "3bd7828aa5af4b13b99c191e8b1e884ebfa9ad371b0ce264605d347f135d2568",
    strip_prefix = "protobuf-3.19.4",
    urls = [
        "https://github.com/protocolbuffers/protobuf/archive/v3.19.4.tar.gz",
    ],
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

http_archive(
    name = "com_github_bazelbuild_buildtools",
    sha256 = "ae34c344514e08c23e90da0e2d6cb700fcd28e80c02e23e4d5715dddcb42f7b3",
    strip_prefix = "buildtools-4.2.2",
    urls = [
        "https://github.com/bazelbuild/buildtools/archive/refs/tags/4.2.2.tar.gz",
    ],
)

http_archive(
    name = "bazel_skylib",
    sha256 = "66ffd9315665bfaafc96b52278f57c7e2dd09f5ede279ea6d39b2be471e7e3aa",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.4.2/bazel-skylib-1.4.2.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.4.2/bazel-skylib-1.4.2.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

http_archive(
    name = "catch2",
    sha256 = "5b10cd536fa3818112a82820ce0787bd9f2a906c618429e7c4dea639983c8e88",
    strip_prefix = "Catch2-3.7.0",
    urls = ["https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.0.tar.gz"],
)

http_archive(
    name = "hedron_compile_commands",
    sha256 = "044b148b111e17cee61d8c3aaeed42069f7325460382340afca4919f8265094c",
    strip_prefix = "bazel-compile-commands-extractor-1e08f8e0507b6b6b1f4416a9a22cf5c28beaba93",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/1e08f8e0507b6b6b1f4416a9a22cf5c28beaba93.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "bazel_clang_tidy",
    commit = "e85311053ec3c32ff418b433af4469b9c77e6b16",
    remote = "https://github.com/erenon/bazel_clang_tidy.git",
)

# load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_repository")

BAZEL_CLANG_FORMAT_COMMIT = "1fd2a042798ede8d6f5498ea92287bc1204260fa"

BAZEL_CLANG_FORMAT_SHA = "c1c4bc1ae1ef9f9ec582d30718b56505907ea59e288e4a65a02ce5c14f990c57"

http_archive(
    name = "bazel_clang_format",
    sha256 = BAZEL_CLANG_FORMAT_SHA,
    strip_prefix = "bazel_clang_format-{commit}".format(
        commit = BAZEL_CLANG_FORMAT_COMMIT,
    ),
    url = "https://github.com/oliverlee/bazel_clang_format/archive/{commit}.tar.gz".format(
        commit = BAZEL_CLANG_FORMAT_COMMIT,
    ),
)

git_repository(
    name = "googletest",
    remote = "https://github.com/google/googletest",
    commit = "b514bdc898e2951020cbdca1304b75f5950d1f59"
)

# http_archive(
#     name = "rules_qt",
#     sha256 = BAZEL_CLANG_FORMAT_SHA,
#     url = "https://github.com/oliverlee/bazel_clang_format/archive/{commit}.tar.gz".format(
#         commit = BAZEL_CLANG_FORMAT_COMMIT,
#     ),
# )

# http_archive(
#     name = "rules_qt",
#     sha256 = "bd8253247c0e45e6a180c87083f20910159e36cd67f6b11d5d3d865a61ea52cd",
#     strip_prefix = "rules_qt6-0.0.3",
#     url = "https://github.com/Vertexwahn/rules_qt6/releases/download/v0.0.3/rules_qt6-v0.0.3.tar.gz",
# )

# load("@rules_qt//:fetch_qt.bzl", "fetch_qt6")

# fetch_qt6()

# load("@rules_qt//tools:qt_toolchain.bzl", "register_qt_toolchains")

# register_qt_toolchains()


# # # http_archive(
# # #     name = "bazelci_rules",
# # #     sha256 = "eca21884e6f66a88c358e580fd67a6b148d30ab57b1680f62a96c00f9bc6a07e",
# # #     strip_prefix = "bazelci_rules-1.0.0",
# # #     url = "https://github.com/bazelbuild/continuous-integration/releases/download/rules-1.0.0/bazelci_rules-1.0.0.tar.gz",
# # # )

# # BAZEL_CLANG_FORMAT_COMMIT = "ad5f2572518053b36a2d999f7b824fb5a7819ab4"

# # BAZEL_CLANG_FORMAT_SHA = "c31f0ea477dd0da84fc2c694a533797a9d2bf060f8cca8b5ea30402a47a2ea0a"

# # http_archive(
# #     name = "bazel_clang_format",
# #     sha256 = BAZEL_CLANG_FORMAT_SHA,
# #     strip_prefix = "bazel_clang_format-{commit}".format(
# #         commit = BAZEL_CLANG_FORMAT_COMMIT,
# #     ),
# #     url = "https://github.com/oliverlee/bazel_clang_format/archive/{commit}.tar.gz".format(
# #         commit = BAZEL_CLANG_FORMAT_COMMIT,
# #     ),
# # )

# # http_archive(
# #     name = "ranges",
# #     integrity = "sha256-AVrbIwCpjt/OrwclvuwzN/VCr0kVzsTQuJ+giG9Lqcs=",
# #     strip_prefix = "range-v3-0.12.0",
# #     url = "https://github.com/ericniebler/range-v3/archive/refs/tags/0.12.0.tar.gz",
# # )

# # http_archive(
# #     name = "magic_enum",
# #     integrity = "sha256-Yln+Zimm2GUIGtKRGlvOi2h/jQhq4EVg4tfOOIPp6o0=",
# #     strip_prefix = "magic_enum-0.9.5",
# #     url = "https://github.com/Neargye/magic_enum/archive/refs/tags/v0.9.5.zip",
# # )

