
load('//:src/util/blender_export.bzl', 'blender_script')
load("@rules_proto_grpc//cpp:defs.bzl", "cpp_grpc_library")

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

cpp_grpc_library(
  name = "proto_cc",
  deps = ["proto_lib"],
)

cc_library(
  name = "client_lib",
  srcs = glob(["src/**/*.cpp",
               "libs/*/*.h",
               "libs/*/*.hpp"],
              exclude = ["src/server.cpp"]),
  hdrs = glob(["src/**/*.h"]),
  copts = ["-I/usr/include/bullet/",
           "-Ilibs/tinygltf/"],
  deps = [":proto_cc"],
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
           "-Ilibs/tinygltf/"],
  deps = [":proto_cc"],
)

cc_binary(
  name = "server",
  deps = ["server_lib"],
  linkopts = ["-lm",
              "-lGLEW",
              "-lGL",
              "-lstdc++",
              "-lLinearMath",
              "-lBulletDynamics",
              "-lBulletCollision",
              "-lBulletSoftBody"],
)
