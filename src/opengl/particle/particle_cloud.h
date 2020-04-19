#ifndef _PARTICLE_CLOUD_H
#define _PARTICLE_CLOUD_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "opengl/shader.h"
#include "particle.h"
#include <vector>

class ParticleCloud {
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
    GLuint vao;
    GLuint vertices_vbo;
    GLuint sizes_vbo;
    GLuint colors_vbo;
    Shader* shader;
    std::vector<Particle*> particles;
    glm::vec3 position;
    Material* material;

  public:
    ParticleCloud(int count, float size, float area, Material* material, std::string shader_name);
    void set_position(glm::vec3 position);
    void update();
    glm::mat4 get_transform();
    Material* get_material();
    Shader* get_shader();
    GLuint get_vao();
    GLuint get_length();
    void add();
  private:
    void update_vbos();
};

#endif
