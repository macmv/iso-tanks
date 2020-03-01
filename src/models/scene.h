#ifndef _SCENE_H
#define _SCENE_H

#include "model_instance.h"
#include <unordered_set>

class Scene {
  public:
    glm::mat4 transform;
    std::unordered_set<ModelInstance*>* models;

  public:
    Scene();
    void add(ModelInstance* model);
};

#endif
