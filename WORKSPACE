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
    sha256 = "438c91a917cc8aa19e82c6f59f8714da353c488584a007d401efac8368e1c785",
    )

# http_archive(
#     name = "reactphysics3d",
#     build_file_content = all_content,
#     strip_prefix = "reactphysics3d-0.7.1",
#     urls = ["https://github.com/DanielChappuis/reactphysics3d/archive/v0.7.1.zip"],
#     sha256 = "4e74a13d7f9861fd87abe2a7585e8ad04f66afc2e274fd28e735551df8d7f535",
#     )

# new_git_repository(
#     name = "reactphysics3d",
#     build_file_content = all_content,
#     commit = "43510811895b4ee3d50841a3d44fb0cee775139e",
#     remote = "https://github.com/DanielChappuis/reactphysics3d.git",
#     )

new_local_repository(
    name = "reactphysics3d",
    build_file_content = all_content,
    path = "libs/reactphysics3d/"
    )

http_archive(
    name = "grpc",
    strip_prefix = "grpc-1.29.1",
    urls = ["https://github.com/grpc/grpc/archive/v1.29.1.tar.gz"],
    sha256 = "0343e6dbde66e9a31c691f2f61e98d79f3584e03a11511fad3f10e3667832a45"
    )

load("@grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
