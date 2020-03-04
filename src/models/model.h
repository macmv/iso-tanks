#ifndef _MODEL_H
#define _MODEL_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "material.h"
#include <string>

class Model {
  public:
    GLuint vao;
    uint length;
    Material* material;
    const std::string name;

  public:
    Model(std::string name);
    Model(std::string name, GLuint vao, uint length);
};

#endif
