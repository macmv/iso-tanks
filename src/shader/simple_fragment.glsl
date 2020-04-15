#version 330 core
in vec3 surface_normal;
in vec3 to_light_vec;

uniform vec3 color;

out vec4 out_color;

void main() {
  float brightness = dot(normalize(surface_normal), normalize(to_light_vec));
  brightness = brightness / 2 + 0.5;
  out_color = vec4(color * (brightness + 0.2), 1);
}
