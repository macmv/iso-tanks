#include "render.h"
#include <cstdlib>
#include <GL/glew.h>
#include <stdio.h>
#include "../world/world.h"
#include "display.h"
#include "loader.h"
#include <iostream>
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

Render::Render(World* world) {
  this->world = world;
  display = new Display();

  createPrograms();

  camera = new Camera(programID);
}

void Render::createPrograms() {
  programID = loadShaderProgram("src/shader/flat_vertex.glsl", "src/shader/flat_geometry.glsl", "src/shader/flat_fragment.glsl");
  // programID = loadShaderProgram("src/shader/simple_vertex.glsl", "src/shader/simple_fragment.glsl");
}

void Render::update(ModelInstance* instance) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!display->update()) {
    display->close();
    exit(0);
  }

  glUseProgram(programID);

  camera->update(display);
  camera->load(instance);

  //instance->transform = glm::rotate(instance->transform, glm::radians(1.f), glm::vec3(0, 1, 0));

  glBindVertexArray(instance->model->vao);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glDrawElements(GL_TRIANGLES, instance->model->length, GL_UNSIGNED_INT, 0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);

  glUseProgram(NULL);

  display->render();
}
