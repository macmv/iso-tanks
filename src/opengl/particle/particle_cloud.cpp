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

ParticleCloud::ParticleCloud(float chance_to_spawn, int num_to_spawn, float area, float lifetime, Particle* base_particle, string shader_name) {
  this->chance_to_spawn = chance_to_spawn;
  this->num_to_spawn = num_to_spawn;
  this->area = area;
  this->lifetime = lifetime;
  this->time_spawned = clock() / CLOCKS_PER_SEC;
  this->base_particle = base_particle;
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
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &colors_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void ParticleCloud::update() {
  if (lifetime < 0 || clock() / CLOCKS_PER_SEC - time_spawned < lifetime) {
    if (rand() % 10000 / 10000.0 <= chance_to_spawn) {
      for(int i = 0; i < num_to_spawn; i++) {
        particles.push_back(base_particle->duplicate(glm::vec3(rand() % 10000 / 10000.0 * area,
                                                               rand() % 10000 / 10000.0 * area,
                                                               rand() % 10000 / 10000.0 * area) + position));
      }
    }
  }
  Particle* particle;
  for (size_t i = 0; i < particles.size(); i++) {
    particle = particles.at(i);
    particle->update();
    if (!particle->alive()) {
      particles.erase(particles.begin() + i--);
      delete particle;
    }
  }
  update_vbos();
}

void ParticleCloud::update_vbos() {
  std::vector<glm::vec3> vertices;
  std::vector<float> sizes;
  std::vector<glm::vec3> colors;

  for (Particle* particle : particles) {
    vertices.push_back(particle->get_position());
    sizes.push_back(particle->get_size());
    colors.push_back(particle->get_material()->color);
  }

  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, sizes_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizes.size() * sizeof(float), sizes.data(), GL_DYNAMIC_DRAW);
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
  return base_particle->get_material();
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
