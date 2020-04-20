#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <glm/glm.hpp>
#include "models/material.h"

class Particle {
  private:
    glm::vec3 position;
    glm::vec2 size;
    Material* material;
    clock_t last_update;

  public:
    Particle(glm::vec3 position, glm::vec2 size, Material* material);
    Particle(glm::vec2 size, Material* material);
    glm::vec3 get_position();
    glm::vec2 get_size();
    Material* get_material();
    void update();
    bool alive();
    Particle* duplicate(glm::vec3 position);
};

#endif
