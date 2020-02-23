#include "debug.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <GL/glew.h>
#include <iostream>

using namespace std;

void DebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)  {
  points[0] = from.x();
  points[1] = from.y();
  points[2] = from.z();
  points[3] = 0;
  points[4] = 0;
  points[5] = color.x();
  points[6] = color.y();
  points[7] = color.z();

  points[8] = to.x();
  points[9] = to.y();
  points[10] = to.z();
  points[11] = 0;
  points[12] = 0;
  points[13] = color.x();
  points[14] = color.y();
  points[15] = color.z();

  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points) * sizeof(GLfloat), &points, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
  glBindVertexArray(0);

  glBindVertexArray(VAO);
  glDrawArrays(GL_LINES, 0, 2);
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
