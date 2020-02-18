#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 surfaceNormal;
out vec3 toLightVec;

void main() {
  vec3 lightPos = vec3(0, 5, 5);

  vec3 world_pos = (model * vec4(pos, 1)).xyz;

  vec4 screen_pos = projection * view * vec4(world_pos, 1);
  gl_Position = screen_pos;

  surfaceNormal = (model * vec4(normal, 1)).xyz;
  toLightVec = lightPos - world_pos;
}
