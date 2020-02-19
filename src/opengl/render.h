#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "../world/world.h"
#include "display.h"
#include "camera.h"
#include "../models/model_instance.h"

#ifndef _RENDER_H
#define _RENDER_H

class Render {
  public:
    World* world;
  private:
    Display* display;
    Camera* camera;
    GLuint programID;

  public:
    Render();
    void update(ModelInstance* model);

  private:
    void createPrograms();
};

#endif
