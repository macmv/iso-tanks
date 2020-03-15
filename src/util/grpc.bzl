
def _cc_grpc_proto(ctx):
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
    command = "protoc {} --cpp_out {} --grpc_out {} --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin".format(proto_file.path, output_path, output_path)
    ctx.actions.run_shell(
      outputs = [header, source, grpc_header, grpc_source],
      inputs = [proto_file],
      command = command,
    )

  return [DefaultInfo(files=depset(files))]

cc_grpc_proto = rule(
  implementation = _cc_grpc_proto,
  attrs = {
    "srcs": attr.label_list(allow_files=True),
  },
)

def _cc_grpc_library(ctx):
  headers = []
  includes = []
  if not ctx.attr.deps:
    fail("Need exactly 1 item in deps", "deps")
  generated = ctx.attr.deps[0].files.to_list()
  for proto_file in generated:
    print(proto_file)
    name = proto_file.path[0:-len(proto_file.extension) - 1]
    source_object = ctx.actions.declare_file(name + ".pb.o")
    grpc_object = ctx.actions.declare_file(name + ".grpc.pb.o")
    print(proto_file.dirname)
    ctx.actions.cc_library(
      outputs = [source_object, grpc_object],
      inputs = [proto_file],
    )

  return [
    CcInfo(compilation_context=cc_common.create_compilation_context(
      includes=depset(includes),
      headers=depset(headers)))]

cc_grpc_library = rule(
  implementation = _cc_grpc_library,
  attrs = {
    "deps": attr.label_list(allow_rules=["cc_grpc_proto"]),
  },
)
