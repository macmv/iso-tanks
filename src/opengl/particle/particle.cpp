#include "particle.h"
#include <glm/glm.hpp>

Particle::Particle(glm::vec3 position, glm::vec2 size, glm::vec3 color) {
  this->position = position;
  this->size = size;
  this->color = color;
}

glm::vec3 Particle::get_position() {
  return position;
}

glm::vec2 Particle::get_size() {
  return size;
}

glm::vec3 Particle::get_color() {
  return color;
}

