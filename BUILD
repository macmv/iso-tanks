
load('//:src/util/blender_export.bzl', 'blender_script')
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

blender_script(
  name = "assets",
  script = "src/util/blender_export.py",
  srcs = glob(["assets/**/*.blend"]),
)

filegroup(
  name = "shaders",
  srcs = glob(["src/shader/**/*.glsl"]),
)


proto_library(
  name = "proto_lib",
  srcs = glob(["src/proto/**/*.proto"]),
)

cc_proto_library(
  name = "proto_cc",
  deps = ["proto_lib"],
)

cc_grpc_library(
  name = "proto_cc_grpc",
  srcs = [":proto_lib"],
  deps = [":proto_cc"],
  grpc_only = True,
)

cc_library(
  name = "client_lib",
  srcs = glob(["src/**/*.cpp",
               "libs/*/*.h",
               "libs/*/*.hpp"],
              exclude = ["src/server.cpp"]),
  hdrs = glob(["src/**/*.h"]),
  copts = ["-I/usr/include/bullet/",
           "-I/usr/include/grpcpp/",
           "-Ilibs/tinygltf/",
           "-Isrc/"],
  deps = [":proto_cc_grpc"],
)

cc_binary(
  name = "client",
  deps = ["client_lib"],
  linkopts = ["-lsfml-system",
              "-lsfml-window",
              "-lm",
              "-lGLEW",
              "-lGL",
              "-lstdc++",
              "-lgrpc",
              "-lgrpc++",
              "-lLinearMath",
              "-lBulletDynamics",
              "-lBulletCollision",
              "-lBulletSoftBody"],
  data = [
    ":shaders",
    ":assets",
  ],
)

cc_library(
  name = "server_lib",
  srcs = glob(["src/**/*.cpp",
               "libs/*/*.h",
               "libs/*/*.hpp"],
              exclude = ["src/client.cpp"]),
  hdrs = glob(["src/**/*.h"]),
  copts = ["-I/usr/include/bullet/",
           "-Ilibs/tinygltf/",
           "-Isrc/"],
  deps = [":proto_cc_grpc"],
)

cc_binary(
  name = "server",
  deps = ["server_lib"],
  linkopts = ["-lsfml-system",
              "-lsfml-window",
              "-lm",
              "-lGLEW",
              "-lGL",
              "-lstdc++",
              "-lgrpc",
              "-lgrpc++",
              "-lLinearMath",
              "-lBulletDynamics",
              "-lBulletCollision",
              "-lBulletSoftBody"],
)
