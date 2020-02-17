#include <glm/glm.hpp>
#include <GL/glew.h>

#ifndef _CAMERA_H
#define _CAMERA_H

class Camera {
  private:
    glm::mat4 projection;
    glm::mat4 view;
    GLuint projectionID;
    GLuint viewID;

  public:
    Camera(GLuint programID);
    void update();
    void update_size(uint width, uint height);
};

#endif
