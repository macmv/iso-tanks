
cc_library(
  name = "compile",
  srcs = glob(["src/**/*.cpp",
               "libs/*/*.h",
               "libs/*/*.hpp"]),
  hdrs = glob(["src/**/*.h"]),
  copts = ["-I/usr/include/bullet/",
           "-Ilibs/tinygltf/"],
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
)
