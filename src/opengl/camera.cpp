#include "camera.h"
#include "models/model_instance.h"
#include "display.h"
#include "shader.h"
#include "player/player.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <SFML/Window.hpp>

using namespace std;

Camera::Camera() {
  projection = glm::perspective(
    glm::radians(70.f), // The vertical Field of View
    16.0f / 9.0f,       // Aspect Ratio
    0.1f,               // Near clipping plane
    3000.0f              // Far clipping plane
  );
  pos = glm::vec3(0, 0, 10);
  dir = glm::vec3(0, 0, 1);
}

void Camera::setPlayerTransform(glm::mat4* transform) {
  playerTransform = transform;
}

void Camera::update(Display* display, Player* player) {
  glm::vec3 up = glm::vec3(0, 1, 0);
  glm::vec3 forward = glm::vec3(0, 0, 1);
  glm::vec3 pos = glm::vec3(0, 3, 0);

  glm::vec3 camForward = glm::normalize(dir);
  glm::vec3 camLeft = cross(up, camForward);

  sf::Vector2i new_pos = sf::Mouse::getPosition();
  display->reset_mouse();
  sf::Vector2i delta;
  if (new_pos.x != 0) {
    delta = display->get_center() - new_pos;
  } else {
    delta = new_pos;
  }
  mouseDelta.x = glm::radians(delta.x * 0.05f);
  mouseDelta.y = glm::radians(delta.y * 0.05f);
  dir = glm::rotate(dir, glm::radians(0.05f * delta.x), up);
  dir = glm::rotate(dir, glm::radians(-0.05f * delta.y), camLeft);
  if (dir.y < -0.999 || dir.y > 0.999) {
    dir = glm::rotate(dir, glm::radians(0.05f * delta.y), camLeft);
  }

  view = glm::lookAt(
    pos,                    // pos
    pos + dir,              // target
    up) * glm::inverse(*playerTransform); // up
}

void Camera::loadMat(Shader* shader) {
  shader->loadProjection(projection);
  shader->loadView(view);
}

void Camera::update_size(uint width, uint height) {
  projection = glm::perspective(
    glm::radians(70.f),     // The vertical Field of View
    (float) width / height, // Aspect Ratio
    0.1f,                   // Near clipping plane
    100.0f                  // Far clipping plane
  );
}

glm::vec2 Camera::getMouseDelta() {
  return mouseDelta;
}

bool Camera::getMousePressed() {
  return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}
