#version 330 core
in uint pass_color;

out vec4 out_color;

void main() {
  // out_color = vec4(
  //     (pass_color & uint(0xFF0000)) >> 16,
  //     (pass_color & uint(0x00FF00)) >> 8,
  //     (pass_color & uint(0x0000FF)) >> 0,
  //     1);
  out_color = vec4(
      1,
      1,
      1,
      1);
}
