#include "terrain.h"
#include "../../opengl/loader.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Terrain::Terrain(int detail) {
  std::vector<uint> indices;
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;

  double t = (1.0 + sqrt(5.0)) / 2.0;
  scale = 10;
  this->detail = detail;

  std::vector<glm::vec3> points;

  points.push_back(glm::vec3(-1,  t,  0));
  points.push_back(glm::vec3( 1,  t,  0));
  points.push_back(glm::vec3(-1, -t,  0));
  points.push_back(glm::vec3( 1, -t,  0));

  points.push_back(glm::vec3( 0, -1,  t));
  points.push_back(glm::vec3( 0,  1,  t));
  points.push_back(glm::vec3( 0, -1, -t));
  points.push_back(glm::vec3( 0,  1, -t));

  points.push_back(glm::vec3( t,  0, -1));
  points.push_back(glm::vec3( t,  0,  1));
  points.push_back(glm::vec3(-t,  0, -1));
  points.push_back(glm::vec3(-t,  0,  1));

  // 5 faces around point 0
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(0), points.at(11), points.at(5));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(0), points.at(5),  points.at(1));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(0), points.at(1),  points.at(7));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(0), points.at(7),  points.at(10));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(0), points.at(10), points.at(11));

  // 5 adjacent faces
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(1),  points.at(5),  points.at(9));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(5),  points.at(11), points.at(4));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(11), points.at(10), points.at(2));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(10), points.at(7),  points.at(6));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(7),  points.at(1),  points.at(8));

  // // 5 faces around point 3
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(3), points.at(9), points.at(4));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(3), points.at(4), points.at(2));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(3), points.at(2), points.at(6));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(3), points.at(6), points.at(8));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(3), points.at(8), points.at(9));

  // // 5 adjacent faces
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(4), points.at(9), points.at(5));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(2), points.at(4), points.at(11));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(6), points.at(2), points.at(10));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(8), points.at(6), points.at(7));
  gen_triangle(&indices, &vertices, &uvs, &normals, points.at(9), points.at(8), points.at(1));

  GLuint vao = createVAO(indices, vertices, uvs, normals);
  uint length = indices.size();
  Model* model = new Model(vao, length);
  instance = new ModelInstance(model);
}

void Terrain::gen_triangle(
  std::vector<uint>* indices,
  std::vector<glm::vec3>* vertices,
  std::vector<glm::vec2>* uvs,
  std::vector<glm::vec3>* normals,
  glm::vec3 a,
  glm::vec3 b,
  glm::vec3 c) {

  for (int i = 0; i < detail; i++) {
    for (int j = 0; j < i + 1; j++) {
      glm::vec3 p00;
      glm::vec3 p01;
      glm::vec3 p10;
      glm::vec3 p11;
      if (i == 0) {
        p00 = glm::normalize(glm::lerp(a, lerp(b, c, 0.f), (float) i / detail));
        p10 = glm::normalize(glm::lerp(a, lerp(b, c, 0.f), (float) i / detail));
      } else {
        p00 = glm::normalize(glm::lerp(a, lerp(b, c, (j + 0.f) / i), (float) i / detail));
        p10 = glm::normalize(glm::lerp(a, lerp(b, c, (j + 1.f) / i), (float) i / detail));
      }
      p01 = glm::normalize(glm::lerp(a, glm::lerp(b, c, (float) (j + 0) / (i + 1)), (float) (i + 1) / detail));
      p11 = glm::normalize(glm::lerp(a, glm::lerp(b, c, (float) (j + 1) / (i + 1)), (float) (i + 1) / detail));
      p00 *= scale;
      p01 *= scale;
      p10 *= scale;
      p11 *= scale;
      cout << glm::to_string(p00) << endl;
      //p00 = p00 * (size + noise.get_noise_3d(
      //    p00.x * noiseScale,
      //    p00.y * noiseScale,
      //    p00.z * noiseScale) * size * noiseWeight)
      //p01 = p01 * (size + noise.get_noise_3d(
      //    p01.x * noiseScale,
      //    p01.y * noiseScale,
      //    p01.z * noiseScale) * size * noiseWeight)
      //p10 = p10 * (size + noise.get_noise_3d(
      //    p10.x * noiseScale,
      //    p10.y * noiseScale,
      //    p10.z * noiseScale) * size * noiseWeight)
      //p11 = p11 * (size + noise.get_noise_3d(
      //    p11.x * noiseScale,
      //    p11.y * noiseScale,
      //    p11.z * noiseScale) * size * noiseWeight)
      if (j < i) {
        vertices->push_back(p10);
        uvs->push_back(glm::vec2(0, 0));
        normals->push_back(glm::vec3(0, 0, 0));

        indices->push_back(vertices->size() - 1);
        indices->push_back(vertices->size() + 2);
        indices->push_back(vertices->size());
      }
      vertices->push_back(p00);
      uvs->push_back(glm::vec2(0, 0));
      normals->push_back(glm::vec3(0, 0, 0));
      vertices->push_back(p01);
      uvs->push_back(glm::vec2(0, 0));
      normals->push_back(glm::vec3(0, 0, 0));
      vertices->push_back(p11);
      uvs->push_back(glm::vec2(0, 0));
      normals->push_back(glm::vec3(0, 0, 0));

      indices->push_back(vertices->size() - 1);
      indices->push_back(vertices->size() - 2);
      indices->push_back(vertices->size() - 3);
    }
  }
}
