#include "scene.h"

Scene::Scene() {
  models = new std::unordered_set<ModelInstance*>();
}

void Scene::add(ModelInstance* model) {
  models->insert(model);
}

Scene* Scene::new_instance() {
  Scene* new_scene = new Scene();
  for (ModelInstance* instance : *models) {
    new_scene->add(instance->new_instance());
  }
  return new_scene;
}

