#include "model_instance.h"

ModelInstance::ModelInstance(Model* model) {
  this->model = model;
  this->transform = glm::mat4();
}

