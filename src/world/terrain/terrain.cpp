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
  double size = 10;

  std::vector<glm::vec3> points;

  points.push_back(glm::vec3(-size,  t * size,  0));
  points.push_back(glm::vec3( size,  t * size,  0));
  points.push_back(glm::vec3(-size, -t * size,  0));
  points.push_back(glm::vec3( size, -t * size,  0));

  points.push_back(glm::vec3( 0, -size,  t * size));
  points.push_back(glm::vec3( 0,  size,  t * size));
  points.push_back(glm::vec3( 0, -size, -t * size));
  points.push_back(glm::vec3( 0,  size, -t * size));

  points.push_back(glm::vec3( t * size,  0, -size));
  points.push_back(glm::vec3( t * size,  0,  size));
  points.push_back(glm::vec3(-t * size,  0, -size));
  points.push_back(glm::vec3(-t * size,  0,  size));

  // 5 faces around point 0
  gen_triangle(&indices, &vertices, &uvs, &normals, detail, points.at(0), points.at(11), points.at(5));
  // gen_triangle(indices, vertices, uvs, normals, detail, points.at(0), points.at(5),  points.at(1));
  // gen_triangle(indices, vertices, uvs, normals, detail, points.at(0), points.at(1),  points.at(7));
  // gen_triangle(indices, vertices, uvs, normals, detail, points.at(0), points.at(7),  points.at(10));
  // gen_triangle(indices, vertices, uvs, normals, detail, points.at(0), points.at(10), points.at(11));

  for (int i = 0; i < indices.size(); i++) {
    std::cout << indices[i] << std::endl;
  }
  for (int i = 0; i < vertices.size(); i++) {
    std::cout << glm::to_string(vertices[i]) << std::endl;
  }

  // 5 adjacent faces
  // min_max_len = gen_triangle(st, min_max_len, points[1], points[5], points[9])
  // min_max_len = gen_triangle(st, min_max_len, points[5], points[11], points[4])
  // min_max_len = gen_triangle(st, min_max_len, points[11], points[10], points[2])
  // min_max_len = gen_triangle(st, min_max_len, points[10], points[7], points[6])
  // min_max_len = gen_triangle(st, min_max_len, points[7], points[1], points[8])

  // // 5 faces around point 3
  // min_max_len = gen_triangle(st, min_max_len, points[3], points[9], points[4])
  // min_max_len = gen_triangle(st, min_max_len, points[3], points[4], points[2])
  // min_max_len = gen_triangle(st, min_max_len, points[3], points[2], points[6])
  // min_max_len = gen_triangle(st, min_max_len, points[3], points[6], points[8])
  // min_max_len = gen_triangle(st, min_max_len, points[3], points[8], points[9])

  // // 5 adjacent faces
  // min_max_len = gen_triangle(st, min_max_len, points[4], points[9], points[5])
  // min_max_len = gen_triangle(st, min_max_len, points[2], points[4], points[11])
  // min_max_len = gen_triangle(st, min_max_len, points[6], points[2], points[10])
  // min_max_len = gen_triangle(st, min_max_len, points[8], points[6], points[7])
  // min_max_len = gen_triangle(st, min_max_len, points[9], points[8], points[1])

  // indices.push_back(0);
  // indices.push_back(1);
  // indices.push_back(2);
  // vertices.push_back(glm::vec3(0, 0, 0));
  // vertices.push_back(glm::vec3(0, 1, 0));
  // vertices.push_back(glm::vec3(1, 0, 0));
  // uvs.push_back(glm::vec2(0, 0));
  // uvs.push_back(glm::vec2(0, 1));
  // uvs.push_back(glm::vec2(1, 0));
  // normals.push_back(glm::vec3(0, 0, 0));
  // normals.push_back(glm::vec3(0, 1, 0));
  // normals.push_back(glm::vec3(1, 0, 0));

  GLuint vao = createVAO(indices, vertices, uvs, normals);
  uint length = indices.size();
  Model* model = new Model(vao, length);
  instance = new ModelInstance(model);
}

void gen_triangle(
  std::vector<uint>* indices,
  std::vector<glm::vec3>* vertices,
  std::vector<glm::vec2>* uvs,
  std::vector<glm::vec3>* normals,
  int detail,
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

        indices->push_back(vertices->size() + 2);
        indices->push_back(vertices->size() - 1);
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
      indices->push_back(vertices->size() - 3);
      indices->push_back(vertices->size() - 2);
    }
  }
}
