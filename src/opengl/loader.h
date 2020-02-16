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
  std::vector < glm::vec3 > & out_vertices,
  std::vector < glm::vec2 > & out_uvs,
  std::vector < glm::vec3 > & out_normals
);

#endif
