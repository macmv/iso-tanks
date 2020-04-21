#include "particle_manager.h"

using namespace std;

ParticleManager::ParticleManager(Render* render) {
  this->m_render = render;
}

void ParticleManager::add(ParticleCloud* cloud) {
  clouds.push_back(cloud);
}

void ParticleManager::update() {
  for (ParticleCloud* cloud : clouds) {
    cloud->update();
  }
}

void ParticleManager::render() {
  for (ParticleCloud* cloud : clouds) {
    m_render->render(cloud);
  }
}
