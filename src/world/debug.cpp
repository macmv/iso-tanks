#include "debug.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

using namespace std;

DebugRender::DebugRender(rp3d::DebugRenderer& renderer) : render(renderer) {
  render.setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
  render.setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, true);
  render.setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
  render.setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_POINT, true);
  render.setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_NORMAL, true);

  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(rp3d::Vector3) + sizeof(int), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(rp3d::Vector3) + sizeof(int), (const void*) sizeof(rp3d::Vector3));
  glBindVertexArray(0);
}

void DebugRender::update() {
  const uint len_triangles = render.getNbTriangles();
  const rp3d::DebugRenderer::DebugTriangle* triangles = render.getTrianglesArray();

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(rp3d::DebugRenderer::DebugTriangle) * len_triangles, triangles, GL_DYNAMIC_DRAW);

  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glDrawArrays(GL_TRIANGLES, 0, len_triangles * 3);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);

  const uint len_lines = render.getNbLines();
  const rp3d::DebugRenderer::DebugLine* lines = render.getLinesArray();

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(rp3d::DebugRenderer::DebugLine) * len_lines, lines, GL_DYNAMIC_DRAW);

  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glDrawArrays(GL_LINES, 0, len_lines * 2);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
}

