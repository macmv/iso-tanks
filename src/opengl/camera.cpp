#include "camera.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <SFML/Window.hpp>

using namespace std;

Camera::Camera(GLuint programID) {
  projection = glm::perspective(
    glm::radians(70.f), // The vertical Field of View
    16.0f / 9.0f,       // Aspect Ratio
    0.1f,               // Near clipping plane
    100.0f              // Far clipping plane
  );
  view = glm::lookAt(
    glm::vec3(0,4,10), // pos
    glm::vec3(0,0,0), // target
    glm::vec3(0,1,0)  // up
  );
  projectionID = glGetUniformLocation(programID, "projection");
  viewID = glGetUniformLocation(programID, "view");
}

void Camera::update() {
  float speed = 0.1;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    view = glm::translate(view, glm::vec3(0, 0, speed));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    view = glm::translate(view, glm::vec3(speed, 0, 0));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    view = glm::translate(view, glm::vec3(0, 0, -speed));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    view = glm::translate(view, glm::vec3(-speed, 0, 0));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    view = glm::translate(view, glm::vec3(0, -speed, 0));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
    view = glm::translate(view, glm::vec3(0, speed, 0));
  }
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
