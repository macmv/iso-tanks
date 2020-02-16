#include <glm/glm.hpp>

#ifndef _CAMERA_H
#define _CAMERA_H

class Camera {
  private:
    glm::mat4 projection;

  public:
    Camera();
};

#endif
