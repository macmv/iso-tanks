#include <glm/glm.hpp>
#include "model.h"

#ifndef _MODEL_INSTANCE_H
#define _MODEL_INSTANCE_H

class ModelInstance {
  public:
    Model* model;
    glm::mat4 transform;

  public:
    ModelInstance(Model* model);
};

#endif
