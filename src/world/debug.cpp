#include "debug.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

using namespace std;

DebugRender::DebugRender(rp3d::DebugRenderer& renderer) : render(renderer) {
  render.setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_NORMAL, true);

  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glBindVertexArray(0);
}

void DebugRender::update() {
  int length = render.getNbLines();
  const rp3d::DebugRenderer::DebugLine* lines = render.getLinesArray();

  vector<glm::vec3> line_data;

  rp3d::Vector3 v;
  for (int i = 0; i < length; i++) {
    v = lines[i].point1;
    line_data.push_back(glm::vec3(v.x, v.y, v.z));
    v = lines[i].point2;
    line_data.push_back(glm::vec3(v.x, v.y, v.z));
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * length * 2, &line_data[0][0], GL_DYNAMIC_DRAW);

  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glDrawArrays(GL_LINES, 0, length);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
}

