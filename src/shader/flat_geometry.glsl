#version 460 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

flat out vec4 pass_color;

void set_pos(int i) {
  vec3 lightPos = vec3(0, 5, 5);

  vec3 world_pos = (model * gl_in[i].gl_Position).xyz;

  vec4 screen_pos = projection * view * vec4(world_pos, 1);
  gl_Position = screen_pos;

  EmitVertex();
}

void main() {
  vec3 lightPos = vec3(0, 5, 5);

  vec3 pos = ((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3).xyz;
  vec3 world_pos = (model * vec4(pos, 1)).xyz;

  vec3 normal = cross(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz);
  vec3 surfaceNormal = (model * vec4(normal, 1)).xyz;
  vec3 toLightVec = lightPos - world_pos;

  float brightness = dot(normalize(surfaceNormal), normalize(toLightVec));
  pass_color = vec4(brightness);

  set_pos(0);
  set_pos(1);
  set_pos(2);
  EndPrimitive();
}
