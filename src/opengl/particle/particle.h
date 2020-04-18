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
    float size;
    // range of randomness of size
    float size_range;
    // area to spread out all the particles
    float area;
  private:
    glm::vec3 position;
    Material* material;
    Shader* shader;
    GLuint vao;

  public:
    Particle(int count, float size, float area, Material* material, std::string shader_name);
    void set_position(glm::vec3 position);
    glm::mat4 get_transform();
    Material* get_material();
    Shader* get_shader();
    GLuint get_vao();
    GLuint get_length();
};

#endif
