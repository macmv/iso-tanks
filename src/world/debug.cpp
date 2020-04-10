#include "debug.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

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
}

void DebugDraw::renderLines() {
  int length = lineData->size();

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * length * 3, &lineData[0][0], GL_STATIC_DRAW);

  glBindVertexArray(VAO);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glDrawArrays(GL_LINES, 0, length / 2);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
}

void DebugDraw::start() {
  delete lineData;
  lineData = new std::vector<glm::vec3>();
}

void DebugDraw::end() {
  renderLines();
  lineData->clear();
  lineData->shrink_to_fit();
}

void DebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)  {
  lineData->push_back(glm::vec3(from.x(), from.y(), from.z()));
  lineData->push_back(glm::vec3(color.x(), color.y(), color.z()));
  lineData->push_back(glm::vec3(to.x(), to.y(), to.z()));
  lineData->push_back(glm::vec3(color.x(), color.y(), color.z()));
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
