import bpy
import sys

argv = sys.argv[sys.argv.index("--") + 1:]
path = argv[0]

bpy.ops.export_scene.gltf(filepath=path)
