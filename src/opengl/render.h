class Render;

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
    Camera* camera;
  private:
    Display* display;

  public:
    Render();
    void add_shader(std::string name, Shader* shader);
    void start(Player* player);   // updates camera and checks window events
    void use(std::string shader); // starts using a shader program, and loads varius matrices
    void end();                   // resets shader program
    void update();                // updates display
    void render(Scene* scene);    // renders scene
    void render(ModelInstance* instance); // renders model

  private:
    void createPrograms();
};

#endif
