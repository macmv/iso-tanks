
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
  shared_libraries = ["libsfml-system.so.2.5",
                      "libsfml-window.so.2.5",
                      "libsfml-graphics.so.2.5"],
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
  srcs = glob(["src/**/*.cpp"],
              exclude = ["src/server.cpp"]),
  hdrs = glob(["src/**/*.h",
               "libs/tinygltf/*.h",
               "libs/tinygltf/*.hpp",
               "@sfml/include/**/*"]),
  copts = ["-I/usr/include/bullet/",
           "-Ilibs/tinygltf/",
           "-Isrc/"],
  deps = [":proto_cc_grpc", ":sfml"],
)

cc_binary(
  name = "client",
  deps = [":client_lib", ":sfml"],
  linkopts = ["-lGLEW",
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
