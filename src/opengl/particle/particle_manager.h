#ifndef _PARTICLE_MANAGER_H
#define _PARTICLE_MANAGER_H

#include "particle_cloud.h"
#include "opengl/render.h"
#include <vector>

class Render;

class ParticleManager {
  private:
    std::unordered_map<uint, ParticleCloud*> clouds;
    std::unordered_map<std::string, Shader*> shaders;
    Render* m_render;
    uint last_id = 1;

  public:
    ParticleManager(Render* render);
    void add(std::string shader_name);
    uint add(ParticleCloud* cloud);
    Shader* get_shader(std::string shader_name);
    ParticleCloud* get(uint id);
    void update();
    void render();
};

#endif
