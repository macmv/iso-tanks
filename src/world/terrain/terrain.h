class Terrain;

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "../../models/model_instance.h"
#include <vector>

class Terrain {
  public:
    ModelInstance* instance;
    std::vector<uint>* indices;
    std::vector<glm::vec3>* vertices;
    std::vector<glm::vec2>* uvs;
    std::vector<glm::vec3>* normals;
  private:
    int detail;
    float scale;

  public:
    Terrain(int detail);
    void createModel();

  private:
    void gen_triangle(
      std::vector<uint>* indices,
      std::vector<glm::vec3>* vertices,
      std::vector<glm::vec2>* uvs,
      std::vector<glm::vec3>* normals,
      glm::vec3 a,
      glm::vec3 b,
      glm::vec3 c);
};

float layered_noise(glm::vec3 pos, int layers, float roughness, float persistence);

#endif
