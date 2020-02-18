#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "../../models/model_instance.h"
#include <vector>

class Terrain {
  public:
    ModelInstance* instance;
  private:
    int detail;
    float scale;

  public:
    Terrain(int detail);

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

#endif
