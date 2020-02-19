#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "../models/model.h"

#ifndef _LOADER_H
#define _LOADER_H

using namespace std;

GLuint loadShaderProgram(string vertexFilename, string fragmentFilename);
GLuint loadShaderProgram(string vertexFilename, string geometryFilename, string fragmentFilename);

bool loadModel(string path, Model* model);

GLuint createVAO(
  std::vector<unsigned int>* indices,
  std::vector<glm::vec3>* vertices,
  std::vector<glm::vec2>* uvs,
  std::vector<glm::vec3>* normals
);

#endif
