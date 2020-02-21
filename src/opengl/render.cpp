#include "render.h"
#include <cstdlib>
#include <GL/glew.h>
#include <stdio.h>
#include "../world/world.h"
#include "display.h"
#include "loader.h"
#include <iostream>
#include "camera.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

Render::Render() {
  display = new Display();

  shaders = new unordered_map<string, Shader*>();

  camera = new Camera(0);
}

void Render::add_shader(string name, Shader* shader) {
  shaders->insert({ name, shader });
}

void Render::start(string shader) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!display->update()) {
    display->close();
    exit(0);
  }

  glUseProgram(shaders->at(shader)->programID);

  camera->update(display);
}

void Render::end() {
  glUseProgram(NULL);
}

void Render::update() {
  display->render();
}

void Render::render(ModelInstance* instance) {
  camera->loadTransform(instance);

  glBindVertexArray(instance->model->vao);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glDrawElements(GL_TRIANGLES, instance->model->length, GL_UNSIGNED_INT, 0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
}
