#include "material.h"

Material::Material() {
  this->color = glm::vec3(0, 0, 0);
}

Material::Material(glm::vec3 color) {
  this->color = color;
}
