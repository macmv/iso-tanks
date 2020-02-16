#include "render.h"
#include <cstdlib>
#include <GL/glew.h>
#include <stdio.h>
#include "../world/world.h"
#include "display.h"
#include "loader.h"
#include <iostream>

Render::Render(World* world) {
  display = new Display();

  createPrograms();
}

void Render::createPrograms() {
  programID = loadShaderProgram("shader/vertex.glsl", "shader/fragment.glsl");
}

void Render::update() {
  glClear(GL_COLOR_BUFFER_BIT);
  display->update();

  glUseProgram(programID);
  glUseProgram(NULL);

  display->render();
}
