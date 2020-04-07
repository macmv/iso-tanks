#version 330 core
in vec3 surfaceNormal;
in vec3 toLightVec;

uniform vec3 color;

out vec4 out_color;

void main() {
  float brightness = dot(normalize(surfaceNormal), normalize(toLightVec));
  brightness = brightness / 2 + 0.5;
  out_color = vec4(color * (brightness + 0.2), 1);
}
