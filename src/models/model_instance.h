#include <glm/glm.hpp>
#include "model.h"

#ifndef _MODEL_INSTANCE_H
#define _MODEL_INSTANCE_H

class ModelInstance {
  private:
    Model* model;
    glm::mat4 transform;

  public:
    ModelInstance(Model* model);
    Model* getModel();
    glm::mat4 getTransform();
};

#endif
