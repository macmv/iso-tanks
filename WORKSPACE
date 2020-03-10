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

