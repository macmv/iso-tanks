#include "scene.h"

Scene::Scene() {
  models = new std::unordered_set<ModelInstance*>();
}

void Scene::add(ModelInstance* model) {
  models->insert(model);
}

