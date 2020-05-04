#include "shader.h"
#include "loader.h"
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include "../models/material.h"

using namespace std;

Shader::Shader(string filename, bool has_geometry) {
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  geometry_shader = 0;
  if (has_geometry) {
    geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
  }

  bool res = Loader::load_shader(vertex_shader, filename + "_vertex.glsl");
  if (!res) {
    exit(1);
  }
  res = Loader::load_shader(fragment_shader, filename + "_fragment.glsl");
  if (!res) {
    exit(1);
  }
  if (geometry_shader != 0) {
    res = Loader::load_shader(geometry_shader, filename + "_geometry.glsl");
    if (!res) {
      exit(1);
    }
  }

  program_id = glCreateProgram();

  glAttachShader(program_id, vertex_shader);
  glAttachShader(program_id, fragment_shader);
  if (geometry_shader != 0) {
    glAttachShader(program_id, geometry_shader);
  }

  glLinkProgram(program_id);

  projection_id = glGetUniformLocation(program_id, "projection");
  view_id       = glGetUniformLocation(program_id, "view");
  model_id      = glGetUniformLocation(program_id, "model");
  color_id      = glGetUniformLocation(program_id, "color");
  aspect_id     = glGetUniformLocation(program_id, "aspect");
}

Shader::~Shader() {
  glDetachShader(program_id, vertex_shader);
  glDetachShader(program_id, fragment_shader);
  if (geometry_shader != 0) {
    glDetachShader(program_id, geometry_shader);
  }
  glDeleteProgram(program_id);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  if (geometry_shader != 0) {
    glDeleteShader(geometry_shader);
  }
}

void Shader::load_projection(glm::mat4 projection) {
  glUniformMatrix4fv(projection_id, 1, GL_FALSE, &projection[0][0]);
}

void Shader::load_view(glm::mat4 view) {
  glUniformMatrix4fv(view_id, 1, GL_FALSE, &view[0][0]);
}

void Shader::load_model(glm::mat4 model) {
  glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
}

void Shader::load_aspect(float aspect) {
  glUniform1f(aspect_id, aspect);
}

void Shader::load_material(Material* material) {
  if (material != NULL) {
    glUniform3f(color_id, material->color.x, material->color.y, material->color.z);
  }
}

