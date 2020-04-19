#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <glm/glm.hpp>

class Particle {
  private:
    glm::vec3 position;
    glm::vec2 size;
    glm::vec3 color;
    clock_t time_created;

  public:
    Particle(glm::vec3 position, glm::vec2 size, glm::vec3 color);
    glm::vec3 get_position();
    glm::vec2 get_size();
    glm::vec3 get_color();
    bool alive();
};

#endif
