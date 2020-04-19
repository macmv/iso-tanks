#version 330 core
in vec4 pass_color;
in vec2 pass_uv;

out vec4 out_color;

void main() {
  out_color = pass_color;
}
