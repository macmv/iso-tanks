#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SFML/Window.hpp>

#ifndef _CAMERA_H
#define _CAMERA_H

class Camera {
  private:
    glm::mat4 projection;
    glm::vec3 pos;
    glm::vec3 dir;
    GLuint projectionID;
    GLuint viewID;
    sf::Vector2i old_pos;

  public:
    Camera(GLuint programID);
    void update();
    void update_size(uint width, uint height);
};

#endif
