#include "debug.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

using namespace std;

DebugDraw::DebugDraw() {
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glBindVertexArray(0);

  points = (GLfloat*) malloc(0);
}

void DebugDraw::renderLines() {
  int length = lineData->size();
  points = (GLfloat*) malloc(sizeof(GLfloat) * length * 3);

  btVector3 val;
  for (int i = 0; i < length; i++) {
    val = lineData->at(i);
    points[i * 3 + 0] = val.x();
    points[i * 3 + 1] = val.y();
    points[i * 3 + 2] = val.z();
  }

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * length * 3, points, GL_STATIC_DRAW);

  glBindVertexArray(VAO);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glDrawArrays(GL_LINES, 0, length / 2);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);

  free(points);
}

void DebugDraw::start() {
  lineData = new std::vector<btVector3>();
}

void DebugDraw::end() {
  renderLines();
  lineData->clear();
  lineData->shrink_to_fit();
}

void DebugDraw::clean() {
  free(points);
}

void DebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)  {
  lineData->push_back((btVector3) from);
  lineData->push_back((btVector3) color);
  lineData->push_back((btVector3) to);
  lineData->push_back((btVector3) color);
}

void DebugDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {

}

void DebugDraw::reportErrorWarning(const char* warningString) {

}

void DebugDraw::draw3dText(const btVector3& location, const char* textString) {
}

void DebugDraw::setDebugMode(int debugMode) {
  mode = debugMode;
}

int DebugDraw::getDebugMode() const {
  return mode;
}
