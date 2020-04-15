#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "models/model.h"
#include "models/scene.h"

#ifndef _LOADER_H
#define _LOADER_H

using namespace std;

bool load_shader(GLuint shader, string filename);

bool load_model(string path, Model* model);
bool load_scene(string path, Scene* scene);

GLuint create_vao(
  std::vector<unsigned int>* indices,
  std::vector<glm::vec3>* vertices,
  std::vector<glm::vec2>* uvs,
  std::vector<glm::vec3>* normals
);

#endif
