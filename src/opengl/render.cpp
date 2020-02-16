#include "render.h"
#include <cstdlib>
#include <GL/glew.h>
#include <stdio.h>
#include "../world/world.h"
#include "display.h"
#include "loader.h"
#include <iostream>

Render::Render(World* world) {
  this->world = world;
  display = new Display();

  createPrograms();
}

void Render::createPrograms() {
  programID = loadShaderProgram("src/shader/vertex.glsl", "src/shader/fragment.glsl");
}

void Render::update(uint vao) {
  glClear(GL_COLOR_BUFFER_BIT);
  display->update();

  glUseProgram(programID);

  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);

  glUseProgram(NULL);

  display->render();
}
