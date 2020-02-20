#ifndef _CAMERA_H
#define _CAMERA_H

#include "display.h"
#include "../models/model_instance.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SFML/Window.hpp>

class Camera {
  private:
    glm::mat4 projection;
    glm::vec3 pos;
    glm::vec3 dir;
    GLuint projectionID;
    GLuint viewID;
    GLuint modelID;
    sf::Vector2i old_pos;

  public:
    Camera(GLuint programID);
    void update(Display* display);
    void update_size(uint width, uint height);
    void set_mouse(uint x, uint y);
    void loadTransform(ModelInstance* model);
};

#endif
