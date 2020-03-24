
load('//:src/util/blender_export.bzl', 'blender_script')
load('//:src/util/grpc.bzl', 'cc_grpc_library')
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
               "libs/*/*.h",
               "libs/*/*.hpp"],
              exclude = ["src/server.cpp"]),
  hdrs = glob(["src/**/*.h"]),
  copts = ["-I/usr/include/bullet/",
           "-Ilibs/tinygltf/",
           "-Isrc/"],
  deps = [":proto_cc_grpc"],
)

cc_binary(
  name = "client",
  deps = ["client_lib"],
  linkopts = ["-lsfml-system",
              "-lsfml-window",
              "-lsfml-graphics",
              "-lGLEW",
              "-lGL",
              "-lgrpc++",
              "-lprotobuf",
              "-lpthread",
              "-lLinearMath",
              "-lBulletDynamics",
              "-lBulletCollision",
              "-lBulletSoftBody"],
  data = [
    ":shaders",
    ":fonts",
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
              "-lGLEW",
              "-lGL",
              "-lgrpc++",
              "-lprotobuf",
              "-lpthread",
              "-lLinearMath",
              "-lBulletDynamics",
              "-lBulletCollision",
              "-lBulletSoftBody"],
)
