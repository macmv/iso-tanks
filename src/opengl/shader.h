#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "models/material.h"

class Shader {
  private:
    GLuint projectionID;
    GLuint viewID;
    GLuint modelID;
    GLuint colorID;
  public:
    GLuint programID;

  public:
    Shader(std::string filename, bool has_geometry);
    void loadProjection(glm::mat4 projection);
    void loadView(glm::mat4 view);
    void loadModel(glm::mat4 model);
    void loadMaterial(Material* material);
};

#endif
