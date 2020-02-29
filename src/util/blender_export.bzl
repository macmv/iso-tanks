
def _blender_script(ctx):
  print("Blender export!")
  files = []
  for input_file in ctx.files.srcs:
    output_filename = input_file.path.split(".")[0] + ".obj"
    output_file = ctx.actions.declare_file(output_filename)
    print(output_file.path)
    files.append(output_file)
    ctx.actions.run_shell(
      outputs = [output_file],
      inputs = [input_file, ctx.file.script],
      command = "blender {} -b -P {} -- {} 1> /dev/null 2> /dev/null".format(input_file.path, ctx.file.script.path, output_file.path),
    )
  return [DefaultInfo(files = depset(files), runfiles = ctx.runfiles(files))]

blender_script = rule(
  implementation = _blender_script,
  attrs = {
    "script": attr.label(allow_single_file=True),
    "srcs": attr.label_list(allow_files=True),
  }
)
