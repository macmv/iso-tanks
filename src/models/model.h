#ifndef _MODEL_H
#define _MODEL_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "material.h"

class Model {
  public:
    GLuint vao;
    uint length;
    Material* material;

  public:
    Model();
    Model(GLuint vao, uint length);
};

#endif
