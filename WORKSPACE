load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_github_grpc_grpc",
    urls = ["https://github.com/grpc/grpc/archive/v1.27.3.tar.gz"],
    sha256 = "c2ab8a42a0d673c1acb596d276055adcc074c1116e427f118415da3e79e52969",
    strip_prefix = "grpc-1.27.3",
    )

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()

# Group the sources of the library so that CMake rule have access to it
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

# Rule repository
http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-master",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
    sha256 = "3e83c1a3f9ddc512eb9b45a9c16df2f6738e8769302b3042826d9443fb57e3fd"
    )

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

http_archive(
    name = "sfml",
    build_file_content = all_content,
    strip_prefix = "SFML-2.5.1",
    urls = ["https://github.com/SFML/SFML/archive/2.5.1.tar.gz"],
    sha256 = "438c91a917cc8aa19e82c6f59f8714da353c488584a007d401efac8368e1c785"
    )

http_archive(
    name = "bullet",
    build_file_content = all_content,
    strip_prefix = "bullet3-2.89",
    urls = ["https://github.com/bulletphysics/bullet3/archive/2.89.tar.gz"],
    sha256 = "621b36e91c0371933f3c2156db22c083383164881d2a6b84636759dc4cbb0bb8",
    )

http_archive(
    name = "grpc",
    strip_prefix = "grpc-1.28.1",
    urls = ["https://github.com/grpc/grpc/archive/v1.28.1.tar.gz"],
    sha256 = "4cbce7f708917b6e58b631c24c59fe720acc8fef5f959df9a58cdf9558d0a79b"
    )

load("@grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
