#ifndef _RENDER_H
#define _RENDER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "world/client_world.h"
#include "display.h"
#include "camera.h"
#include "shader.h"
#include "models/model_instance.h"
#include <unordered_map>
#include <SFML/Graphics/Font.hpp>
#include "ui_render.h"
#include "ui/hud.h"
#include "particle/particle_cloud.h"
#include "particle/particle_manager.h"

class UIRender;
class Hud;
class ClientWorld;
class ParticleManager;

class Render {
  public:
    ClientWorld* world;
    std::unordered_map<std::string, Shader*>* shaders;
    Shader* current_shader;
    Camera* camera;
    Display* display;
    UIRender* ui_render;
    ParticleManager* particle_manager;
  private:
    Hud* hud;

  public:
    Render();
    void add_shader(std::string name, Shader* shader);
    void start(ControlledPlayer* player);   // updates camera and checks window events
    void use(std::string shader); // starts using a shader program, and loads varius matrices
    void end();                   // resets shader program
    void finish();                // updates display and renders hud
    void render(Scene* scene);    // renders scene
    void render(ModelInstance* instance); // renders model
    void render(ParticleCloud* cloud); // renders particle cloud

  private:
    void create_programs();
};

#endif
