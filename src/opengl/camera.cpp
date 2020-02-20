#include "camera.h"
#include "../models/model_instance.h"
#include "display.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <SFML/Window.hpp>

using namespace std;

Camera::Camera(GLuint programID) {
  projection = glm::perspective(
    glm::radians(70.f), // The vertical Field of View
    16.0f / 9.0f,       // Aspect Ratio
    0.1f,               // Near clipping plane
    100.0f              // Far clipping plane
  );
  pos = glm::vec3(0, 0, 10);
  dir = glm::vec3(0, 0, -1);
  projectionID = glGetUniformLocation(programID, "projection");
  viewID = glGetUniformLocation(programID, "view");
  modelID = glGetUniformLocation(programID, "model");
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
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    pos += glm::vec3(0, speed, 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
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

  glm::mat4 view = glm::lookAt(
    pos,               // pos
    pos + dir,         // target
    glm::vec3(0,1,0)); // up
  glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);
  glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
}

void Camera::loadTransform(ModelInstance* model) {
  glUniformMatrix4fv(modelID, 1, GL_FALSE, &model->transform[0][0]);
}

void Camera::update_size(uint width, uint height) {
  projection = glm::perspective(
    glm::radians(70.f),     // The vertical Field of View
    (float) width / height, // Aspect Ratio
    0.1f,                   // Near clipping plane
    100.0f                  // Far clipping plane
  );
}
