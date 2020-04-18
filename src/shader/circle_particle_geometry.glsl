#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float aspect;

in vec3 color[];
in vec2 uv[];

out vec4 pass_color;

vec4 pos;
mat4 view_model;

void add_point(vec2 offset) {
  gl_Position = projection * pos + vec4(offset, 0, 0);
  EmitVertex();
};

void main() {
  pos = view * model * gl_in[0].gl_Position;

  float w = uv[0].x / 2;
  float h = uv[0].y / 2 * aspect;

  pass_color = vec4(color[0], 0);
  add_point(vec2(-w, -h));
  add_point(vec2(w, -h));
  add_point(vec2(-w, h));
  add_point(vec2(w, h));
  EndPrimitive();
}
