#version 330 core
const float PI = 3.1415926535897932384626433832795;

layout (points) in;
layout (triangle_strip, max_vertices = 24) out; // (num_verts - 2) * 3

uniform mat4 projection;
uniform mat4 view;
uniform float aspect;

in vec3 color[];
in float size[];

out vec4 pass_color;
out vec2 pass_uv;

vec4 pos;
mat4 view_model;

void add_point(vec2 offset) {
  gl_Position = pos + vec4(offset, 0, 0);
  EmitVertex();
};

void main() {
  pos = projection * view * gl_in[0].gl_Position;

  float w = size[0] / 2;
  float h = size[0] / 2 * aspect;

  pass_color = vec4(color[0], 1);
  int num_verts = 10;
  float r, x, y, prev_x, prev_y;
  for (float i = 1; i < num_verts; i++) {
    r = i / num_verts * 2 * PI;
    x = cos(r);
    y = sin(r);
    if (i == 1) {
      prev_x = x;
      prev_y = y;
      continue;
    }
    pass_uv = vec2(1, .5);
    add_point(vec2(w, 0));
    pass_uv = vec2(prev_x, prev_y);
    add_point(vec2(prev_x * w, prev_y * h));
    pass_uv = vec2(x, y);
    add_point(vec2(x * w, y * h));
    prev_x = x;
    prev_y = y;
    EndPrimitive();
  }
}
