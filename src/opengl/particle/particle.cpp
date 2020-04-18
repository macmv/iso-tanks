#include "particle.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

Particle::Particle(int count, float size, float area) {
  this->count = count;
  this->size = size;
  this->area = area;
}

glm::mat4 Particle::get_transform() {
  glm::mat4 transform = glm::mat4(1);
  transform[3] = transform[3] + glm::vec4(position, 0);
  return transform;
}

Material* Particle::get_material() {
  return material;
}
