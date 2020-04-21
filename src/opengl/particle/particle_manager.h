#ifndef _PARTICLE_MANAGER_H
#define _PARTICLE_MANAGER_H

#include "particle_cloud.h"
#include "opengl/render.h"
#include <vector>

class Render;

class ParticleManager {
  private:
    std::vector<ParticleCloud*> clouds;
    Render* m_render;

  public:
    ParticleManager(Render* render);
    void add(ParticleCloud* cloud);
    void update();
    void render();
};

#endif
