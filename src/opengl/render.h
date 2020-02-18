#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "../world/world.h"
#include "display.h"
#include "camera.h"
#include "../models/model_instance.h"

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
    void update(ModelInstance* model);

  private:
    void createPrograms();
};

#endif
