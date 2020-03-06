
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
  name = "compile",
  srcs = glob(["src/**/*.cpp",
               "libs/*/*.h",
               "libs/*/*.hpp"]),
  hdrs = glob(["src/**/*.h"]),
  copts = ["-I/usr/include/bullet/",
           "-Ilibs/tinygltf/"],
  deps = [":proto_cc"],
)

cc_binary(
  name = "iso-tanks",
  deps = ["compile"],
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
