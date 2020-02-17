#include "render.h"
#include <cstdlib>
#include <GL/glew.h>
#include <stdio.h>
#include "../world/world.h"
#include "display.h"
#include "loader.h"
#include <iostream>
#include "camera.h"

Render::Render(World* world) {
  this->world = world;
  display = new Display();

  createPrograms();

  camera = new Camera(programID);
}

void Render::createPrograms() {
  programID = loadShaderProgram("src/shader/vertex.glsl", "src/shader/fragment.glsl");
}

void Render::update(Model* model) {
  glClear(GL_COLOR_BUFFER_BIT);
  if (!display->update(camera)) {
    display->close();
    exit(0);
  }

  glUseProgram(programID);

  camera->update();

  glBindVertexArray(model->vao);
  glEnableVertexAttribArray(0);
  glDrawElements(GL_TRIANGLES, model->length, GL_UNSIGNED_INT, 0);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);

  glUseProgram(NULL);

  display->render();
}
