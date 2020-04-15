#include "model_instance.h"

ModelInstance::ModelInstance(Model* model) {
  this->model = model;
  transform = glm::mat4(1);
}

ModelInstance* ModelInstance::new_instance() {
  ModelInstance* new_instance = new ModelInstance(model);
  new_instance->transform = transform;
  return new_instance;
}

