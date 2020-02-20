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
    void start();  // starts using a shader program, and loads varius matrices
    void end();    // resets shader program
    void update(); // updates display
    void render(ModelInstance* model); // renders object

  private:
    void createPrograms();
};

#endif
