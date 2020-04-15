#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec3 color[];

flat out vec4 pass_color;

void set_pos(int i) {
  vec3 world_pos = (model * gl_in[i].gl_Position).xyz;

  vec4 screen_pos = projection * view * vec4(world_pos, 1);
  gl_Position = screen_pos;

  EmitVertex();
}

void main() {
  vec3 light_pos = vec3(0, 0, 0);
  float specular_strength = 0.5;
  float diffuse_strength = 1;
  vec3 cam = vec3(0, 0, 10);

  // matrix maths
  vec3 pos = ((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3).xyz;
  vec3 world_pos = (model * vec4(pos, 1)).xyz;

  // diffuse lighting
  vec3 normal = cross(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz);
  vec3 surface_normal = normalize((model * vec4(normal, 1)).xyz);
  vec3 to_light_vec = normalize(light_pos - world_pos);
  float brightness = dot(surface_normal, to_light_vec);
  float diffuse = brightness * diffuse_strength;

  // specular lighting
  vec3 cam_dir = normalize(cam - world_pos);
  vec3 reflect_dir = reflect(-to_light_vec, surface_normal);
  float spec = pow(max(dot(cam_dir, reflect_dir), 0.0), 32);
  float specular = specular_strength * spec;

  // final color
  pass_color = vec4(diffuse * color[0], 1);

  set_pos(0);
  set_pos(1);
  set_pos(2);
  EndPrimitive();
}
