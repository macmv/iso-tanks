#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "../world/world.h"
#include "display.h"
#include "camera.h"
#include "shader.h"
#include "../models/model_instance.h"
#include <unordered_map>

#ifndef _RENDER_H
#define _RENDER_H

class Render {
  public:
    World* world;
    std::unordered_map<std::string, Shader*>* shaders;
    Shader* currentShader;
  private:
    Display* display;
    Camera* camera;

  public:
    Render();
    void add_shader(std::string name, Shader* shader);
    void start();                  // updates camera and checks window events
    void use(std::string shader);  // starts using a shader program, and loads varius matrices
    void end();    // resets shader program
    void update(); // updates display
    void render(ModelInstance* model); // renders object

  private:
    void createPrograms();
};

#endif
