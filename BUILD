
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
  name = "bullet",
  lib_source = "@bullet//:all",
  cmake_options = ["-DBUILD_SHARED_LIBS=ON",
                   "-DINSTALL_LIBS=ON",
                   "-DINSTALL_EXTRA_LIBS=ON",
                   "-DBUILD_PYBULLET=OFF",
                   "-DUSE_DOUBLE_PRECISION=OFF",
                   "-DBUILD_UNIT_TESTS=OFF",
                   "-DCMAKE_BUILD_TYPE=Release"],
  make_commands = ["make -j $(command nproc 2>/dev/null || echo 12)", "make install"],
  shared_libraries = ["libBulletExampleBrowserLib.so.2.89",
                      "libgwen.so",
                      "libBussIK.so",
                      "libOpenGLWindow.so",
                      "libBulletInverseDynamicsUtils.so.2.89",
                      "libBulletRobotics.so.2.89",
                      "libBulletFileLoader.so.2.89",
                      "libBulletXmlWorldImporter.so.2.89",
                      "libBulletWorldImporter.so.2.89",
                      "libConvexDecomposition.so.2.89",
                      "libHACD.so.2.89",
                      "libGIMPACTUtils.so.2.89",
                      "libBullet3OpenCL_clew.so.2.89",
                      "libBullet2FileLoader.so.2.89",
                      "libBullet3Dynamics.so.2.89",
                      "libBullet3Collision.so.2.89",
                      "libBullet3Geometry.so.2.89",
                      "libBulletInverseDynamics.so.2.89",
                      "libBulletSoftBody.so.2.89",
                      "libBulletCollision.so.2.89",
                      "libBulletDynamics.so.2.89",
                      "libLinearMath.so.2.89",
                      "libBullet3Common.so.2.89"],
)

cmake_external(
  name = "jsoncpp",
  lib_source = "@jsoncpp//:all",
  cmake_options = ["-DBUILD_SHARED_LIBS=ON",
                   "-DBUILD_STATIC_LIBS=OFF",
                   "-DINSTALL_LIBS=ON"],
  make_commands = ["make -j $(command nproc 2>/dev/null || echo 12)", "make install"],
  shared_libraries = ["libjsoncpp.so.23"],
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
              exclude = ["src/server.cpp", "src/test.cpp"]),
  hdrs = glob(["src/**/*.h",
               "libs/tinygltf/*.h",
               "libs/tinygltf/*.hpp",
               "@sfml/include/**/*"]),
  copts = ["-Ilibs/tinygltf/",
#           "-Ibazel-out/k8-fastbuild/bin/bullet/include/bullet/",
           "-Ibazel-out/k8-dbg/bin/bullet/include/bullet/",
           "-Isrc/"],
  deps = [":proto_cc_grpc",
          ":sfml",
          ":bullet",
          ":jsoncpp",
          "@grpc//:grpc++",
          "@com_google_protobuf//:protobuf"],
)

cc_binary(
  name = "client",
  deps = [":client_lib",
          ":sfml",
          ":bullet"],
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
  srcs = glob(["src/**/*.cpp"],
              exclude = ["src/server.cpp", "src/client.cpp"]),
  hdrs = glob(["src/**/*.h",
               "libs/tinygltf/*.h",
               "libs/tinygltf/*.hpp",
               "@sfml/include/**/*"]),
  copts = ["-Ilibs/tinygltf/",
#           "-Ibazel-out/k8-fastbuild/bin/bullet/include/bullet/",
           "-Ibazel-out/k8-dbg/bin/bullet/include/bullet/",
           "-Isrc/"],
  deps = [":proto_cc_grpc",
          ":sfml",
          ":bullet",
          ":jsoncpp",
          "@grpc//:grpc++",
          "@com_google_protobuf//:protobuf"],
)

cc_binary(
  name = "test",
  deps = [":test_lib",
          ":sfml",
          ":bullet"],
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
  srcs = glob(["src/**/*.cpp"],
              exclude = ["src/client.cpp", "src/test.cpp"]),
  hdrs = glob(["src/**/*.h",
               "libs/tinygltf/*.h",
               "libs/tinygltf/*.hpp",
               "@sfml/include/**/*"]),
  copts = ["-Ilibs/tinygltf/",
#           "-Ibazel-out/k8-fastbuild/bin/bullet/include/bullet/",
           "-Ibazel-out/k8-dbg/bin/bullet/include/bullet/",
           "-Isrc/"],
  deps = [":proto_cc_grpc",
          ":sfml",
          ":bullet",
          ":jsoncpp",
          "@grpc//:grpc++",
          "@com_google_protobuf//:protobuf"],
)

cc_binary(
  name = "server",
  deps = [":server_lib",
          ":sfml",
          ":bullet"],
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
