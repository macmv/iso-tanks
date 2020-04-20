#include "particle.h"
#include <glm/glm.hpp>
#include <time.h>
#include <iostream>

using namespace std;

Particle::Particle(glm::vec3 position, glm::vec2 size, Material* material) : Particle(size, material) {
  this->position = position;
}

Particle::Particle(glm::vec2 size, Material* material) {
  this->size = size;
  this->material = material;
  last_update = clock();
}

glm::vec3 Particle::get_position() {
  return position;
}

glm::vec2 Particle::get_size() {
  return size;
}

Material* Particle::get_material() {
  return material;
}

void Particle::update() {
  size -= (float) (clock() - last_update) / CLOCKS_PER_SEC * 0.5f;
  last_update = clock();
}

bool Particle::alive() {
  return size.x > 0 && size.y > 0;
}

Particle* Particle::duplicate(glm::vec3 position) {
  return new Particle(position, size, material);
}

