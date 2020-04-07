#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 in_color;

out vec3 color;

void main() {
  color = in_color;
  gl_Position = vec4(pos, 1);
}
