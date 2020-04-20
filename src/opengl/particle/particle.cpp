#include "particle.h"
#include <glm/glm.hpp>
#include <time.h>
#include <iostream>

using namespace std;

Particle::Particle(glm::vec3 position, float size, float decay_time, Material* material) : Particle(size, decay_time, material) {
  this->position = position;
}

Particle::Particle(float size, float decay_time, Material* material) {
  this->size = size;
  this->material = material;
  this->decay_time = decay_time;
  decay_rate = size / decay_time;
  last_update = clock();
}

glm::vec3 Particle::get_position() {
  return position;
}

float Particle::get_size() {
  return size;
}

Material* Particle::get_material() {
  return material;
}

void Particle::update() {
  size -= (float) (clock() - last_update) / CLOCKS_PER_SEC * decay_rate;
  last_update = clock();
}

bool Particle::alive() {
  return size > 0;
}

Particle* Particle::duplicate(glm::vec3 position) {
  return new Particle(position, size, decay_time, material);
}

