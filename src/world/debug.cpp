#include "debug.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <GL/glew.h>
#include <iostream>

using namespace std;

DebugDraw::DebugDraw() {
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glBindVertexArray(0);
}


void DebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)  {
  points[0] = from.x();
  points[1] = from.y();
  points[2] = from.z();
  points[3] = color.x();
  points[4] = color.y();
  points[5] = color.z();

  points[6] = to.x();
  points[7] = to.y();
  points[8] = to.z();
  points[9] = color.x();
  points[10] = color.y();
  points[11] = color.z();

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

  glBindVertexArray(VAO);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glDrawArrays(GL_LINES, 0, 2);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
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
