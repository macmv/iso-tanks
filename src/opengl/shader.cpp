#include "shader.h"
#include "loader.h"
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>

using namespace std;

Shader::Shader(string filename, bool has_geometry) {
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint geometryShader;
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  if (has_geometry) {
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
  }

  bool res = loadShader(vertexShader, filename + "_vertex.glsl");
  if (!res) {
    exit(1);
  }
  res = loadShader(fragmentShader, filename + "_fragment.glsl");
  if (!res) {
    exit(1);
  }
  if (has_geometry) {
    res = loadShader(geometryShader, filename + "_geometry.glsl");
    if (!res) {
      exit(1);
    }
  }

  programID = glCreateProgram();

  glAttachShader(programID, vertexShader);
  glAttachShader(programID, fragmentShader);
  if (has_geometry) {
    glAttachShader(programID, geometryShader);
  }

  glLinkProgram(programID);

  projectionID = glGetUniformLocation(programID, "projection");
  viewID = glGetUniformLocation(programID, "view");
  modelID = glGetUniformLocation(programID, "model");
}

void Shader::loadProjection(glm::mat4 projection) {
  glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);
}

void Shader::loadView(glm::mat4 view) {
  glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
}

void Shader::loadModel(glm::mat4 model) {
  glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
}

