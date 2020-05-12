#include "debug.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

using namespace std;

//DebugDraw::DebugDraw() {
//  glGenBuffers(1, &vbo);
//  glGenVertexArrays(1, &vao);
//  glBindVertexArray(vao);
//  glBindBuffer(GL_ARRAY_BUFFER, vbo);
//  glEnableVertexAttribArray(0);
//  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
//  glEnableVertexAttribArray(1);
//  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//  glBindVertexArray(0);
//  line_data = new std::vector<glm::vec3>();
//}
//
//void DebugDraw::render_lines() {
//  int length = line_data->size();
//
//  glBindBuffer(GL_ARRAY_BUFFER, vbo);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * length * 3, &line_data[0][0], GL_STATIC_DRAW);
//
//  glBindVertexArray(vao);
//  glEnableVertexAttribArray(0);
//  glEnableVertexAttribArray(1);
//  glDrawArrays(GL_LINES, 0, length / 2);
//  glDisableVertexAttribArray(0);
//  glDisableVertexAttribArray(1);
//  glBindVertexArray(0);
//}
//
//void DebugDraw::start() {
//  delete line_data;
//  line_data = new std::vector<glm::vec3>();
//}
//
//void DebugDraw::end() {
//  render_lines();
//  line_data->clear();
//  line_data->shrink_to_fit();
//}
//
//void DebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)  {
//  line_data->push_back(glm::vec3(from.x(), from.y(), from.z()));
//  line_data->push_back(glm::vec3(color.x(), color.y(), color.z()));
//  line_data->push_back(glm::vec3(to.x(), to.y(), to.z()));
//  line_data->push_back(glm::vec3(color.x(), color.y(), color.z()));
//}
//
//void DebugDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {
//
//}
//
//void DebugDraw::reportErrorWarning(const char* warningString) {
//
//}
//
//void DebugDraw::draw3dText(const btVector3& location, const char* textString) {
//}
//
//void DebugDraw::setDebugMode(int debugMode) {
//  mode = debugMode;
//}
//
//int DebugDraw::getDebugMode() const {
//  return mode;
//}
