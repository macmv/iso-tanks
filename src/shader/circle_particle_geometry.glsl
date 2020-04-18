#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec3 color[];
in vec2 uv[];

flat out vec4 pass_color;

void main() {
  // matrix maths
  vec3 pos = gl_in[0].gl_Position.xyz;
  vec3 world_pos = (model * vec4(pos, 1)).xyz;

  gl_Position = projection * view * (vec4(world_pos, 1) + vec4(uv[0].x, 0, 0, 0));
  EmitVertex();
  gl_Position = projection * view * (vec4(world_pos, 1) + vec4(0, 0, 0, 0));
  EmitVertex();
  gl_Position = projection * view * (vec4(world_pos, 1) + vec4(uv[0].x, uv[0].y, 0, 0));
  EmitVertex();
  gl_Position = projection * view * (vec4(world_pos, 1) + vec4(0, uv[0].y, 0, 0));
  EmitVertex();
  EndPrimitive();
}
