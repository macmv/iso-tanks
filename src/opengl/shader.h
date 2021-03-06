#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "models/material.h"

class Shader {
  private:
    GLuint projection_id;
    GLuint view_id;
    GLuint model_id;
    GLuint color_id;
    GLuint aspect_id;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint geometry_shader;
  public:
    GLuint program_id;

  public:
    Shader(std::string filename, bool has_geometry);
    ~Shader();
    void load_projection(glm::mat4 projection);
    void load_view(glm::mat4 view);
    void load_model(glm::mat4 model);
    void load_material(Material* material);
    void load_aspect(float aspect);
};

#endif
