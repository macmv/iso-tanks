#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "opengl/shader.h"

class Particle {
  protected:
    // number of particles to render
    int count;
    // size of each particle
    int size;
    // area to spread out all the particles
    float area;
  private:
    glm::vec3 position;
    Material* material;

  public:
    Particle();
    glm::mat4 get_transform();
    Material* get_material();
    virtual Shader* get_shader() = 0;
    virtual GLuint get_vao() = 0;
    virtual GLuint get_length() = 0;
};

#endif
