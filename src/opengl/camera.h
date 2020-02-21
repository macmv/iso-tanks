#ifndef _CAMERA_H
#define _CAMERA_H

#include "display.h"
#include "../models/model_instance.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SFML/Window.hpp>

class Camera {
  private:
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 pos;
    glm::vec3 dir;
    sf::Vector2i old_pos;

  public:
    Camera();
    void update(Display* display);
    void update_size(uint width, uint height);
    void set_mouse(uint x, uint y);
    void loadMat(Shader* shader);
};

#endif
