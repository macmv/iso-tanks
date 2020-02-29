
def _blender_script(ctx):
  print("Blender export!")
  files = []
  for input_file in ctx.files.srcs:
    output_filename = input_file.path + ".obj"
    output_file = ctx.actions.declare_file(output_filename)
    files.append(output_file)
    ctx.actions.run_shell(
      outputs = [output_file],
      inputs = [input_file],
      command = "touch {}".format(output_file.path),
    )
  return [DefaultInfo(files = depset(files), runfiles = ctx.runfiles(files))]

blender_script = rule(
  implementation = _blender_script,
  attrs = {
    "script": attr.label(allow_single_file=True),
    "srcs": attr.label_list(allow_files=True),
  }
)
