
load('//:src/util/blender_export.bzl', 'blender_script')
load('//:src/util/grpc.bzl', 'cc_grpc_library')
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

blender_script(
  name = "assets",
  script = "src/util/blender_export.py",
  srcs = glob(["assets/**/*.blend"]),
)

cmake_external(
  name = "sfml",
  lib_source = "@sfml//:all",
  make_commands = ["make -j $(command nproc 2>/dev/null || echo 12)", "make install"],
#  shared_libraries = ["libsfml-system.so.2.5",
#                      "libsfml-window.so.2.5",
#                      "libsfml-graphics.so.2.5"],
  shared_libraries = ["libsfml-system-d.so.2.5",
                      "libsfml-window-d.so.2.5",
                      "libsfml-graphics-d.so.2.5"],
)

cmake_external(
  name = "reactphysics3d",
  lib_source = "@reactphysics3d//:all",
  #cmake_options = ["-DBUILD_SHARED_LIBS=ON"],
  make_commands = ["make -j $(command nproc 2>/dev/null || echo 12)", "make install"],
  #shared_libraries = ["libreactphysics3d.so.0.7.1"],
  static_libraries = ["libreactphysics3d.a"],
)

filegroup(
  name = "shaders",
  srcs = glob(["src/shader/**/*.glsl"]),
)

filegroup(
  name = "fonts",
  srcs = glob(["assets/**/*.ttf"]),
)

cc_grpc_library(
  name = "proto_cc_grpc",
  srcs = glob(["src/proto/**/*.proto"]),
)

cc_library(
  name = "client_lib",
  srcs = glob(["src/**/*.cpp",
               "libs/tinygltf/**/*.h",
               "libs/tinygltf/**/*.hpp"],
              exclude = ["src/server.cpp", "src/test.cpp"]),
  hdrs = glob(["src/**/*.h"]),
  copts = ["-Ilibs/tinygltf/",
#           "-Ibazel-out/k8-fastbuild/bin/bullet/include/bullet/",
           "-Ibazel-out/k8-dbg/bin/bullet/include/bullet/",
           "-I/usr/include/reactphysics3d/",
           "-Isrc/"],
  deps = [":proto_cc_grpc",
          ":sfml",
          ":reactphysics3d",
          "@grpc//:grpc++",
          "@com_google_protobuf//:protobuf"],
)

cc_binary(
  name = "client",
  deps = [":client_lib"],
  linkopts = ["-lstdc++fs",
              "-lGLEW",
              "-lGL",
              "-lpthread"],
  data = [
    ":shaders",
    ":fonts",
    ":assets"],
)

genrule(
  name = "client_zip",
  srcs = glob(["bazel-out/k8-fastbuild/bin/client.runfiles/__main__/**/*"]),
  tools = ["@bazel_tools//tools/zip:zipper"],
  outs = ["client.zip"],
  cmd = "$(location @bazel_tools//tools/zip:zipper) c $@ $(SRCS)",
)

cc_library(
  name = "test_lib",
  srcs = glob(["src/test.cpp",
               "libs/tinygltf/**/*.h",
               "libs/tinygltf/**/*.hpp"],
              exclude = ["src/server.cpp", "src/client.cpp"]),
  hdrs = glob(["src/**/*.h"]),
  copts = ["-Ilibs/tinygltf/",
#           "-Ibazel-out/k8-fastbuild/bin/bullet/include/bullet/",
           "-Ibazel-out/k8-dbg/bin/bullet/include/bullet/",
           "-I/usr/include/reactphysics3d/",
           "-Isrc/"],
  deps = [":proto_cc_grpc",
          ":sfml",
          ":reactphysics3d",
          "@grpc//:grpc++",
          "@com_google_protobuf//:protobuf"],
)

cc_binary(
  name = "test",
  deps = [":test_lib",
          ":sfml",
          ":reactphysics3d"],
  linkopts = ["-lstdc++fs",
              "-lGLEW",
              "-lGL",
              "-lpthread"],
  data = [
    ":shaders",
    ":fonts",
    ":assets"],
)

genrule(
  name = "test_zip",
  srcs = glob(["bazel-out/k8-fastbuild/bin/test.runfiles/__main__/**/*"]),
  tools = ["@bazel_tools//tools/zip:zipper"],
  outs = ["test.zip"],
  cmd = "$(location @bazel_tools//tools/zip:zipper) c $@ $(SRCS)",
)

cc_library(
  name = "server_lib",
  srcs = glob(["src/**/*.cpp",
               "libs/tinygltf/**/*.h",
               "libs/tinygltf/**/*.hpp"],
              exclude = ["src/client.cpp", "src/test.cpp"]),
  hdrs = glob(["src/**/*.h"]),
  copts = ["-Ilibs/tinygltf/",
#           "-Ibazel-out/k8-fastbuild/bin/bullet/include/bullet/",
           "-Ibazel-out/k8-dbg/bin/bullet/include/bullet/",
           "-I/usr/include/reactphysics3d/",
           "-Isrc/"],
  deps = [":proto_cc_grpc",
          ":sfml",
          ":reactphysics3d",
          "@grpc//:grpc++",
          "@com_google_protobuf//:protobuf"],
)

cc_binary(
  name = "server",
  deps = [":server_lib",
          ":sfml",
          ":reactphysics3d"],
  linkopts = ["-lstdc++fs",
              "-lGLEW",
              "-lGL",
              "-lpthread"],
)

genrule(
  name = "server_zip",
  srcs = glob(["bazel-out/k8-fastbuild/bin/server.runfiles/__main__/**/*"]),
  tools = ["@bazel_tools//tools/zip:zipper"],
  outs = ["server.zip"],
  cmd = "$(location @bazel_tools//tools/zip:zipper) c $@ -d bazel-out/k8-fastbuild/bin/ $(SRCS)",
)
