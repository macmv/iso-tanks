#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in float in_size;
layout (location = 2) in vec3 in_color;

out vec3 color;
out float size;

void main() {
  color = in_color;
  size = in_size;
  gl_Position = vec4(pos, 1);
}
