import bpy

bpy.ops.export_scene.obj(filepath=bpy.data.filepath.split(".")[0] + ".obj", use_triangles=True)
