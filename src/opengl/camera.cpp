#include "camera.h"
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
}

void Camera::update() {
  float speed = 0.1;
  glm::vec3 left = glm::rotate(dir, glm::radians(90.f), glm::vec3(0, 1, 0));
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    pos += glm::vec3(dir.x * speed, 0, dir.z * speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    pos += glm::vec3(left.x * speed, 0, left.z * speed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    pos += glm::vec3(-dir.x * speed, 0, -dir.z * speed);
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
  sf::Vector2i delta = old_pos - new_pos;
  old_pos = new_pos;
  dir = glm::rotate(dir, glm::radians(0.05f * delta.x), glm::vec3(0, 1, 0));

  glm::mat4 view = glm::lookAt(
    pos,               // pos
    pos + dir,         // target
    glm::vec3(0,1,0)); // up
  glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);
  glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
}

void Camera::update_size(uint width, uint height) {
  projection = glm::perspective(
    glm::radians(70.f),     // The vertical Field of View
    (float) width / height, // Aspect Ratio
    0.1f,                   // Near clipping plane
    100.0f                  // Far clipping plane
  );
}
