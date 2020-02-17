#version 460 core
layout (location = 0) in vec3 pos;

uniform mat4 projection;
uniform mat4 view;

out vec4 color;

void main() {
  vec4 screen_pos = projection * view * vec4(pos, 1);
  gl_Position = screen_pos;
  color = vec4(
      min(-screen_pos.x + 1, -screen_pos.y + 1),
      max(screen_pos.x,      -screen_pos.y + 1),
      max(-screen_pos.x + 1,  screen_pos.y),
      1);
}
