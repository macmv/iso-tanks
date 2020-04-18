#include "particle.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include "opengl/loader.h"

using namespace std;

Particle::Particle(int count, float size, float area, Material* material, string shader_name) {
  this->count = count;
  this->size = size;
  this->area = area;
  this->material = material;
  this->shader = new Shader(shader_name, true);
  std::vector<unsigned int>* indices = new std::vector<unsigned int>();
  std::vector<glm::vec3>* vertices = new std::vector<glm::vec3>();
  std::vector<glm::vec2>* uvs = new std::vector<glm::vec2>();
  std::vector<glm::vec3>* normals = new std::vector<glm::vec3>();
  for (int i = 0; i < count; i++) {
    indices->push_back(i);
    vertices->push_back(glm::vec3(rand() % 10000 / 10000.0 * area, rand() % 10000 / 10000.0 * area, rand() % 10000 / 10000.0 * area));
    uvs->push_back(glm::vec2(0, 0));
    normals->push_back(glm::vec3(0, 0, 0));
  }
  vao = Loader::create_vao(indices, vertices, uvs, normals);
}

void Particle::set_position(glm::vec3 position) {
  this->position = position;
}

glm::mat4 Particle::get_transform() {
  glm::mat4 transform = glm::mat4(1);
  transform[3] = transform[3] + glm::vec4(position, 0);
  return transform;
}

Material* Particle::get_material() {
  return material;
}

Shader* Particle::get_shader() {
  return shader;
}

GLuint Particle::get_vao() {
  return vao;
}

GLuint Particle::get_length() {
  return count;
}
