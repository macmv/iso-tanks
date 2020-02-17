#include "model.h"
#include <GL/glew.h>

Model::Model(GLuint vao, uint length) {
  this->vao = vao;
  this->length = length;
}

Model::Model() {
  vao = 0;
  length = 0;
}

