
load('//:src/util/blender_export.bzl', 'blender_script')
load('//:src/util/grpc.bzl', 'cc_grpc_library')
load('//:src/util/grpc.bzl', 'cc_grpc_proto')
# load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

blender_script(
  name = "assets",
  script = "src/util/blender_export.py",
  srcs = glob(["assets/**/*.blend"]),
)

filegroup(
  name = "shaders",
  srcs = glob(["src/shader/**/*.glsl"]),
)

# cc_grpc_library(
#   name = "proto_cc_grpc",
#   srcs = glob(["src/proto/**/*.proto"]),
#   deps = [],
# )

cc_grpc_proto(
  name = "proto_cc_grpc",
  srcs = glob(["src/proto/**/*.proto"]),
)

cc_grpc_library(
  name = "proto_cc_grpc_lib",
  deps = [":proto_cc_grpc"],
)

cc_library(
  name = "client_lib",
  srcs = glob(["src/**/*.cpp",
               "libs/*/*.h",
               "libs/*/*.hpp"],
              exclude = ["src/server.cpp"]),
  hdrs = glob(["src/**/*.h"]),
  copts = ["-I/usr/include/bullet/",
           "-Ilibs/tinygltf/",
           "-Isrc/"],
  deps = [":proto_cc_grpc_lib"],
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
