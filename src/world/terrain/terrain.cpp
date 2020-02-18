#include "terrain.h"
#include "../../opengl/loader.h"
#include <vector>

Terrain::Terrain(int detail) {
  std::vector<uint> indices;
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;

  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(2);
  vertices.push_back(glm::vec3(0, 0, 0));
  vertices.push_back(glm::vec3(0, 1, 0));
  vertices.push_back(glm::vec3(1, 0, 0));
  uvs.push_back(glm::vec2(0, 0));
  uvs.push_back(glm::vec2(0, 1));
  uvs.push_back(glm::vec2(1, 0));
  normals.push_back(glm::vec3(0, 0, 0));
  normals.push_back(glm::vec3(0, 1, 0));
  normals.push_back(glm::vec3(1, 0, 0));

  GLuint vao = createVAO(indices, vertices, uvs, normals);
  uint length = indices.size();
  Model* model = new Model(vao, length);
  instance = new ModelInstance(model);
}
