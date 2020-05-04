#include "particle_manager.h"

using namespace std;

ParticleManager::ParticleManager(Render* render) {
  this->m_render = render;
}

uint ParticleManager::add(ParticleCloud* cloud) {
  clouds.insert({last_id, cloud});
  return last_id++;
}

void ParticleManager::add(string shader_name) {
  shaders.insert({shader_name, new Shader(shader_name, true)});
}

Shader* ParticleManager::get_shader(string shader_name) {
  return shaders.at(shader_name);
}

ParticleCloud* ParticleManager::get(uint id) {
  std::unordered_map<uint, ParticleCloud*>::iterator item = clouds.find(id);
  if (item == clouds.end()) {
    return NULL;
  } else {
    return item->second;
  }
}

void ParticleManager::update() {
  vector<uint> delete_items;
  for (std::pair<uint, ParticleCloud*> item : clouds) {
    item.second->update();
    if (!item.second->alive()) {
      delete_items.push_back(item.first);
      delete item.second;
    }
  }
  for (uint id : delete_items) {
    clouds.erase(id);
  }
}

void ParticleManager::render() {
  for (std::pair<uint, ParticleCloud*> item : clouds) {
    m_render->render(item.second);
  }
}

