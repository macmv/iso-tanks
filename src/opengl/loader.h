#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "models/model.h"
#include "models/scene.h"

#ifndef _LOADER_H
#define _LOADER_H

using namespace std;

bool loadShader(GLuint shader, string filename);

bool loadModel(string path, Model* model);
bool loadScene(string path, Scene* scene);

GLuint createVAO(
  std::vector<unsigned int>* indices,
  std::vector<glm::vec3>* vertices,
  std::vector<glm::vec2>* uvs,
  std::vector<glm::vec3>* normals
);

#endif
