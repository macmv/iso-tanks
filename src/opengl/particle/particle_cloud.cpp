#include "particle_cloud.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include "opengl/loader.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "particle.h"
#include <vector>

using namespace std;

ParticleCloud::ParticleCloud(int count, float size, float area, Material* material, string shader_name) {
  this->count = count;
  this->size = size;
  this->area = area;
  this->material = material;
  this->shader = new Shader(shader_name, true);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vertices_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
  glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &sizes_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, sizes_vbo);
  glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &colors_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void ParticleCloud::update() {
  add();
  add();
  add();
  Particle* particle;
  for (size_t i = 0; i < particles.size(); i++) {
    particle = particles.at(i);
    if (!particle->alive()) {
      particles.erase(particles.begin() + i--);
      delete particle;
    }
  }
  update_vbos();
}

void ParticleCloud::add() {
  particles.push_back(new Particle(glm::vec3(rand() % 10000 / 10000.0 * area,
                                             rand() % 10000 / 10000.0 * area,
                                             rand() % 10000 / 10000.0 * area) + position,
                                   glm::vec2(size),
                                   material->color));
}

void ParticleCloud::update_vbos() {
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> sizes;
  std::vector<glm::vec3> colors;

  for (Particle* particle : particles) {
    vertices.push_back(particle->get_position());
    sizes.push_back(particle->get_size());
    colors.push_back(particle->get_color());
  }

  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, sizes_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizes.size() * sizeof(glm::vec2), sizes.data(), GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleCloud::set_position(glm::vec3 position) {
  this->position = position;
}

glm::mat4 ParticleCloud::get_transform() {
  glm::mat4 transform = glm::mat4(1);
  transform[3] = transform[3] + glm::vec4(position, 0);
  return transform;
}

Material* ParticleCloud::get_material() {
  return material;
}

Shader* ParticleCloud::get_shader() {
  return shader;
}

GLuint ParticleCloud::get_vao() {
  return vao;
}

GLuint ParticleCloud::get_length() {
  return particles.size();
}
