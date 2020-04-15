#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 surface_normal;
out vec3 to_light_vec;

void main() {
  vec3 light_pos = vec3(0, 40, 0);

  vec3 world_pos = (model * vec4(pos, 1)).xyz;

  vec4 screen_pos = projection * view * vec4(world_pos, 1);
  gl_Position = screen_pos;

  surface_normal = (model * vec4(normal, 0)).xyz;
  to_light_vec = light_pos - world_pos;
}
