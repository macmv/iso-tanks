#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <glm/glm.hpp>
#include "models/material.h"

class Particle {
  private:
    glm::vec3 position;
    float size;
    float decay_time;
    float decay_rate;
    Material* material;
    clock_t last_update;

  public:
    Particle(glm::vec3 position, float size, float decay_time, Material* material);
    Particle(float size, float decay_time, Material* material);
    glm::vec3 get_position();
    float get_size();
    Material* get_material();
    void update();
    bool alive();
    Particle* duplicate(glm::vec3 position);
};

#endif
