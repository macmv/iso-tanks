
def cc_grpc_library(
  name,
  srcs,
  **kwargs):

  extra_deps = []
  proto_targets = []

  proto_target = "_" + name + "_only"
  cc_proto_target = "_" + name + "_cc_proto"

  native.cc_proto_library(
    name = cc_proto_target,
    deps = [":" + proto_target],
    **kwargs
  )
  extra_deps.append(":" + cc_proto_target)
  proto_targets.append(proto_target)

  codegen_grpc_target = "_" + name + "_grpc_codegen"
  generate_cc(
    name = codegen_grpc_target,
    srcs = srcs,
    **kwargs
  )

  native.cc_library(
    name = name,
    srcs = [":" + codegen_grpc_target],
    hdrs = [":" + codegen_grpc_target],
    **kwargs
  )

def _generate_cc(ctx):
  files = []
  for proto_file in ctx.files.srcs:
    name = proto_file.path[0:-len(proto_file.extension) - 1]
    header = ctx.actions.declare_file(name + ".pb.h")
    source = ctx.actions.declare_file(name + ".pb.cc")
    grpc_header = ctx.actions.declare_file(name + ".grpc.pb.h")
    grpc_source = ctx.actions.declare_file(name + ".grpc.pb.cc")
    files.append(header)
    files.append(source)
    files.append(grpc_header)
    files.append(grpc_source)
    output_path = header.path[0:-len(name) - 5]
    command = "protoc {} --cpp_out {}".format(proto_file.path, output_path)
    ctx.actions.run_shell(
      outputs = [header, source],
      inputs = [proto_file],
      command = command,
    )
    command = "protoc {} --grpc_out {} --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin".format(proto_file.path, output_path)
    ctx.actions.run_shell(
      outputs = [grpc_header, grpc_source],
      inputs = [proto_file],
      command = command,
    )

  return [DefaultInfo(files=depset(files))]

generate_cc = rule(
  implementation = _generate_cc,
  attrs = {
    "srcs": attr.label_list(allow_files=True),
  },
)
