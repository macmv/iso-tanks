#include "particle.h"
#include <glm/glm.hpp>
#include <time.h>
#include <iostream>

using namespace std;

Particle::Particle(glm::vec3 position, glm::vec2 size, glm::vec3 color) {
  this->position = position;
  this->size = size;
  this->color = color;
  time_created = clock();
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

bool Particle::alive() {
  return (float) (clock() - time_created) / CLOCKS_PER_SEC < .1;
}

