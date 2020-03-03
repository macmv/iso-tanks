import bpy
import sys

bpy.ops.object.select_all(action='SELECT')
bpy.ops.object.visual_transform_apply()

argv = sys.argv[sys.argv.index("--") + 1:]
path = argv[0]

bpy.ops.export_scene.gltf(filepath=path, export_apply=True)
