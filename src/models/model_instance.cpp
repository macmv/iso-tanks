#include "model_instance.h"

ModelInstance::ModelInstance(Model* model) {
  this->model = model;
  transform = glm::mat4(1);
}

