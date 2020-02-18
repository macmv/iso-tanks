#version 460 core
in vec3 surfaceNormal;
in vec3 toLightVec;

out vec4 out_color;

void main() {
  float brightness = dot(normalize(surfaceNormal), normalize(toLightVec));
  out_color = vec4(brightness);
}
