#ifndef _PARTICLE_CLOUD_H
#define _PARTICLE_CLOUD_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "opengl/shader.h"
#include "particle.h"
#include <vector>

class ParticleCloud {
  protected:
    // chance (0-1) that a particle will spawn each frame
    float chance_to_spawn;
    // number of particles to spawn each time chance_to_spawn is hit
    int num_to_spawn;
    // area to spread out all the particles
    float area;
    // number of seconds to keep the cloud alive (negative means forever)
    float lifetime;
  private:
    GLuint vao;
    GLuint vertices_vbo;
    GLuint sizes_vbo;
    GLuint colors_vbo;
    Shader* shader;
    std::vector<Particle*> particles;
    glm::vec3 position;
    Particle* base_particle;
    clock_t time_spawned;

  public:
    ParticleCloud(float chance_to_spawn, int num_to_spawn, float area, float lifetime, Particle* base_particle, Shader* shader);
    ~ParticleCloud();
    void set_position(glm::vec3 position);
    void update();
    bool alive();
    glm::mat4 get_transform();
    Material* get_material();
    Shader* get_shader();
    GLuint get_vao();
    GLuint get_length();
    friend std::ostream& operator << (std::ostream& os, const ParticleCloud& p);
  private:
    void update_vbos();
};

#endif
