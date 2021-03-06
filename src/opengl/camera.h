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
    glm::vec2 mouse_delta = glm::vec2();
    glm::mat4 player_transform;

  public:
    Camera();
    void set_player_transform(glm::mat4* transform);
    void update(Display* display, Player* player);
    void update_size(uint width, uint height);
    void set_mouse(uint x, uint y);
    void load_mat(Shader* shader);
    glm::vec2 get_mouse_delta();
    bool get_mouse_pressed();
};

#endif
