#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 pass_color;

void main() {
  gl_Position = projection * view * vec4(pos, 1);
  pass_color = color;
}
