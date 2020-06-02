#ifndef _DEBUG_H
#define _DEBUG_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <reactphysics3d/reactphysics3d.h>

class DebugRender {
  private:
    GLuint vbo, vao;
    rp3d::DebugRenderer& render;

  public:
    DebugRender(rp3d::DebugRenderer& render);
    void update();
};

#endif
