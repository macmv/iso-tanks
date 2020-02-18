#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 0) in vec2 uv;
layout (location = 0) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;

out vec3 surfaceNormal;
out vec3 toLightVec;

void main() {
  vec3 lightPos = vec3(0, 5, 5);

  vec4 screen_pos = projection * view * vec4(pos, 1);
  gl_Position = screen_pos;

  surfaceNormal = normal;
  toLightVec = lightPos - vec3(0, 0, 0);
}
