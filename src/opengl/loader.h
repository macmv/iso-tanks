#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>

#ifndef _LOADER_H
#define _LOADER_H

using namespace std;

GLuint loadShaderProgram(string vertexFilename, string fragmentFilename);

bool loadOBJ(
  const char* path,
  std::vector<unsigned int>& out_indices,
  std::vector<glm::vec3>& out_vertices,
  std::vector<glm::vec2>& out_uvs,
  std::vector<glm::vec3>& out_normals
);

GLuint createVAO(
  std::vector<unsigned int>& indices,
  std::vector<glm::vec3>& vertices,
  std::vector<glm::vec2>& uvs,
  std::vector<glm::vec3>& normals
);


#endif
