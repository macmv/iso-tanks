#include "terrain.h"
#include "opengl/loader.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/noise.hpp>
#include <iostream>

Terrain::Terrain(int detail) {
  indices = new std::vector<uint>();
  vertices = new std::vector<glm::vec3>();
  uvs = new std::vector<glm::vec2>();
  normals = new std::vector<glm::vec3>();

  double t = (1.0 + sqrt(5.0)) / 2.0;
  scale = 1000;
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
  gen_triangle(indices, vertices, uvs, normals, points.at(0), points.at(11), points.at(5));
  gen_triangle(indices, vertices, uvs, normals, points.at(0), points.at(5),  points.at(1));
  gen_triangle(indices, vertices, uvs, normals, points.at(0), points.at(1),  points.at(7));
  gen_triangle(indices, vertices, uvs, normals, points.at(0), points.at(7),  points.at(10));
  gen_triangle(indices, vertices, uvs, normals, points.at(0), points.at(10), points.at(11));

  // 5 adjacent faces
  gen_triangle(indices, vertices, uvs, normals, points.at(1),  points.at(5),  points.at(9));
  gen_triangle(indices, vertices, uvs, normals, points.at(5),  points.at(11), points.at(4));
  gen_triangle(indices, vertices, uvs, normals, points.at(11), points.at(10), points.at(2));
  gen_triangle(indices, vertices, uvs, normals, points.at(10), points.at(7),  points.at(6));
  gen_triangle(indices, vertices, uvs, normals, points.at(7),  points.at(1),  points.at(8));

  // 5 faces around point 3
  gen_triangle(indices, vertices, uvs, normals, points.at(3), points.at(9), points.at(4));
  gen_triangle(indices, vertices, uvs, normals, points.at(3), points.at(4), points.at(2));
  gen_triangle(indices, vertices, uvs, normals, points.at(3), points.at(2), points.at(6));
  gen_triangle(indices, vertices, uvs, normals, points.at(3), points.at(6), points.at(8));
  gen_triangle(indices, vertices, uvs, normals, points.at(3), points.at(8), points.at(9));

  // 5 adjacent faces
  gen_triangle(indices, vertices, uvs, normals, points.at(4), points.at(9), points.at(5));
  gen_triangle(indices, vertices, uvs, normals, points.at(2), points.at(4), points.at(11));
  gen_triangle(indices, vertices, uvs, normals, points.at(6), points.at(2), points.at(10));
  gen_triangle(indices, vertices, uvs, normals, points.at(8), points.at(6), points.at(7));
  gen_triangle(indices, vertices, uvs, normals, points.at(9), points.at(8), points.at(1));
  instance = NULL;
}

void Terrain::create_model() {
  GLuint vao = create_vao(indices, vertices, uvs, normals);
  uint length = indices->size();
  Model* model = new Model("terrain", vao, length);
  instance = new ModelInstance(model);
}

glm::vec3 get_color(float value) {
  std::vector<std::pair<float, glm::vec3>> colors;
  colors.push_back(std::pair<float, glm::vec3>(.0f,  glm::vec3(1, 1, 1)));
  colors.push_back(std::pair<float, glm::vec3>(.05f, glm::vec3(1, 1, 1)));
  colors.push_back(std::pair<float, glm::vec3>(.1f,  glm::vec3(.4, .2, .15)));
  colors.push_back(std::pair<float, glm::vec3>(.25f, glm::vec3(.1, .5, .3)));
  colors.push_back(std::pair<float, glm::vec3>(.5f,  glm::vec3(.2, .6, .2)));
  colors.push_back(std::pair<float, glm::vec3>(.65f, glm::vec3(.2, .6, .2)));
  colors.push_back(std::pair<float, glm::vec3>(.7f,  glm::vec3(.2, .4, .8)));
  colors.push_back(std::pair<float, glm::vec3>(1.f,  glm::vec3(.1, .2, .8)));
  std::pair<float, glm::vec3> prev;
  value = glm::min(glm::max((value + 2) / 4.f, 0.001f), 1.f);
  for (std::pair<float, glm::vec3> val : colors) {
    if (val.first >= value) {
      return glm::lerp(
          prev.second,
          val.second,
          (value - prev.first) / (val.first - prev.first));
    }
    prev = val;
  }
}

void Terrain::gen_triangle(
  std::vector<uint>* indices,
  std::vector<glm::vec3>* vertices,
  std::vector<glm::vec2>* uvs,
  std::vector<glm::vec3>* normals,
  glm::vec3 a,
  glm::vec3 b,
  glm::vec3 c) {

  int row_start = vertices->size();

  for (int i = 0; i < detail + 1; i++) {
    row_start += i;
    for (int j = 0; j < i + 1; j++) {
      glm::vec3 point;
      if (i == 0) { // div by 0 errors
        point = glm::normalize(a);
      } else {
        point = glm::normalize(glm::lerp(a, lerp(b, c, (float) j / i), (float) i / detail));
      }
      float noise = layered_noise(point, 8, 2, 0.5f);
      point *= scale + (noise * scale / 10);
      vertices->push_back(point);
      uvs->push_back(glm::vec2(0, 0));
      normals->push_back(get_color(noise));
      if (i != detail) {
        // triangle with two points on bottom row and one point on top row
        indices->push_back(row_start + j);
        indices->push_back(row_start + i + j + 2);
        indices->push_back(row_start + i + j + 1);
        if (j != i) {
          // triangle with one point on bottom row and two points on top row
          indices->push_back(row_start + j);
          indices->push_back(row_start + j + 1);
          indices->push_back(row_start + i + j + 2);
        }
      }
    }
  }
}

float layered_noise(glm::vec3 pos, int layers, float roughness, float persistence) {
  float value = 0;
  float frequency = .5f;
  float amplitude = 2;

  for (int i = 0; i < layers; i++) {
    float val = glm::perlin(pos * frequency + glm::vec3(1000, 0, 0)) * amplitude;
    value += val;
    frequency *= roughness;
    amplitude *= persistence;
  }

  return value;
}
