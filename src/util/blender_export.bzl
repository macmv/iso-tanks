
def _blender_script(ctx):
  files = []
  for input_file in ctx.files.srcs:
    output_filename = input_file.path.split(".")[0] + ".glb"
    output_file = ctx.actions.declare_file(output_filename)
    files.append(output_file)
    ctx.actions.run_shell(
      outputs = [output_file],
      inputs = [input_file, ctx.file.script],
      command = "blender {} -noaudio -b -P {} -- {} > /dev/null".format(input_file.path, ctx.file.script.path, output_file.path),
    )
  return [DefaultInfo(files = depset(files), runfiles = ctx.runfiles(files))]

blender_script = rule(
  implementation = _blender_script,
  attrs = {
    "script": attr.label(allow_single_file=True),
    "srcs": attr.label_list(allow_files=True),
  }
)
