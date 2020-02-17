#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "../world/world.h"
#include "display.h"
#include "camera.h"
#include "../models/model.h"

#ifndef _RENDER_H
#define _RENDER_H

class Render {
  private:
    World* world;
    Display* display;
    Camera* camera;
    GLuint programID;

  public:
    Render(World* world);
    void update(Model* model);

  private:
    void createPrograms();
};

#endif
