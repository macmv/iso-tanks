#include "render.h"
#include <cstdlib>
#include <GL/glew.h>
#include <stdio.h>
#include "world/world.h"
#include "display.h"
#include "loader.h"
#include <iostream>
#include "camera.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Graphics/Font.hpp>
#include "ui/hud.h"
#include "particle/particle.h"

using namespace std;

Render::Render() {
  display = new Display();
  shaders = new unordered_map<string, Shader*>();
  camera = new Camera();

  current_shader = NULL;

  ui_render = new UIRender(this, "assets/Hack-Regular.ttf", 24);
  hud = new Hud(ui_render, display->get_window_size().y / 1080.0);
}

void Render::add_shader(string name, Shader* shader) {
  shaders->insert({ name, shader });
}

void Render::start(ControlledPlayer* player) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!display->update()) {
    display->close();
    exit(0);
  }

  camera->update(display, player);
}

void Render::use(string shader) {
  current_shader = shaders->at(shader);
  glUseProgram(current_shader->program_id);
  camera->load_mat(current_shader);
}

void Render::end() {
  current_shader = NULL;
  glUseProgram(0);
}

void Render::update() {
  hud->render(NULL);
  display->render();
}

void Render::render(ModelInstance* instance) {
  if (current_shader == NULL) {
    cout << "Must call Render::start() before Render::render()!" << endl;
    exit(1);
  }
  if (instance == NULL) {
    cout << "Cannot pass NULL ModelInstance* into Render::render()!" << endl;
    exit(1);
  }

  current_shader->load_model(instance->transform);
  current_shader->load_material(instance->model->material);

  glBindVertexArray(instance->model->vao);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glDrawElements(GL_TRIANGLES, instance->model->length, GL_UNSIGNED_INT, 0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
  GLenum err = glGetError();
  if (err != 0) {
    cerr << "Opengl error code: " << err << endl;
    cerr << "Program exiting" << endl;
    exit(1);
  }
}

void Render::render(Scene* scene) {
  if (current_shader == NULL) {
    cout << "Must call Render::start() before Render::render()!" << endl;
    exit(1);
  }

  std::unordered_set<ModelInstance*>* instances = scene->models;

  glm::mat4 prev;

  for (ModelInstance* instance : *instances) {
    prev = instance->transform;
    instance->transform = scene->transform * instance->transform;
    render(instance);
    instance->transform = prev;
  }
}

void Render::render(Particle* particle) {
  if (current_shader != NULL) {
    cout << "Must call Render::render(Particle*) without calling Render::start()!" << endl;
    exit(1);
  }
  Shader* shader = particle->get_shader();
  glUseProgram(shader->program_id);

  camera->load_mat(shader);
  shader->load_model(particle->get_transform());
  shader->load_material(particle->get_material());
  sf::Vector2u size = display->get_window_size();
  shader->load_aspect((float) size.x / size.y);

  glBindVertexArray(particle->get_vao());
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glDrawElements(GL_POINTS, particle->get_length(), GL_UNSIGNED_INT, 0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
  GLenum err = glGetError();
  if (err != 0) {
    cerr << "Opengl error code: " << err << endl;
    cerr << "Program exiting" << endl;
    exit(1);
  }

  glUseProgram(0);
}
