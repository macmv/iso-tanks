#include "camera.h"
#include "../models/model_instance.h"
#include "display.h"
#include "shader.h"
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
    100.0f              // Far clipping plane
  );
  pos = glm::vec3(0, 0, 10);
  dir = glm::vec3(0, 0, -1);
}

void Camera::update(Display* display) {
  float speed = 0.1;
  glm::vec3 forward = glm::normalize(glm::vec3(dir.x, 0, dir.z));
  glm::vec3 left = glm::rotate(forward, glm::radians(90.f), glm::vec3(0, 1, 0));
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    pos += glm::vec3(forward.x * speed, 0, forward.z * speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    pos += glm::vec3(left.x * speed, 0, left.z * speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    pos += glm::vec3(-forward.x * speed, 0, -forward.z * speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    pos += glm::vec3(-left.x * speed, 0, -left.z * speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
    pos += glm::vec3(0, speed, 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    pos += glm::vec3(0, -speed, 0);
  }
  sf::Vector2i new_pos = sf::Mouse::getPosition();
  display->reset_mouse();
  sf::Vector2i delta;
  if (new_pos.x != 0) {
    delta = display->get_center() - new_pos;
  } else {
    delta = new_pos;
  }
  dir = glm::rotate(dir, glm::radians(0.05f * delta.x), glm::vec3(0, 1, 0));
  dir = glm::rotate(dir, glm::radians(-0.05f * delta.y), left);
  if (dir.y < -0.999 || dir.y > 0.999) {
    dir = glm::rotate(dir, glm::radians(0.05f * delta.y), left);
  }

  view = glm::lookAt(
    pos,               // pos
    pos + dir,         // target
    glm::vec3(0,1,0)); // up
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
