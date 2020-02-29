import bpy
import sys

argv = sys.argv[sys.argv.index("--") + 1:]
path = argv[0]

bpy.ops.export_scene.obj(filepath=path, use_triangles=True)
