#include <iostream>
#include "opengl/render.h"
#include "opengl/loader.h"

using namespace std;

int main() {
  World* world;
  Render* render = new Render(world);

  std::vector<uint> indices;
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;
  loadOBJ("assets/test.obj", indices, vertices, uvs, normals);
  GLuint vao = createVAO(indices, vertices, uvs, normals);
  uint length = indices.size();

  while (true) {
    render->update(vao, length);
  }
}
