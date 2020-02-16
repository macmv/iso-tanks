#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "../world/world.h"
#include "display.h"

#ifndef _RENDER_H
#define _RENDER_H

class Render {
  private:
    World* world;
    Display* display;
    GLuint programID;

  public:
    Render(World* world);
    void update();

  private:
    void createPrograms();
};

#endif
