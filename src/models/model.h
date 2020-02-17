#include <glm/glm.hpp>
#include <GL/glew.h>

#ifndef _MODEL_H
#define _MODEL_H

class Model {
  public:
    GLuint vao;
    uint length;

  public:
    Model();
    Model(GLuint vao, uint length);
};

#endif
