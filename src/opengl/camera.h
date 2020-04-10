#ifndef _CAMERA_H
#define _CAMERA_H

#include "display.h"
#include "models/model_instance.h"
#include "shader.h"
#include "player/player.h"
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
    glm::vec2 mouseDelta = glm::vec2();
    glm::mat4* playerTransform;

  public:
    Camera();
    void setPlayerTransform(glm::mat4* transform);
    void update(Display* display, Player* player);
    void update_size(uint width, uint height);
    void set_mouse(uint x, uint y);
    void loadMat(Shader* shader);
    glm::vec2 getMouseDelta();
};

#endif
