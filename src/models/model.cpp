#include "model.h"
#include <GL/glew.h>

using namespace std;

Model::Model(string name) : name(name) {
  vao = 0;
  length = 0;
}

Model::Model(string name, GLuint vao, uint length) : name(name) {
  this->vao = vao;
  this->length = length;
}

