#include "camera.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;

Camera::Camera(GLuint programID) {
  projection = glm::perspective(
    glm::radians(70.f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
    16.0f / 9.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
    0.1f,               // Near clipping plane. Keep as big as possible, or you'll get precision issues.
    100.0f              // Far clipping plane. Keep as little as possible.
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
  glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);
  glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
}
