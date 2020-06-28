#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "opengl/render.h"
#include "opengl/loader.h"
#include "opengl/shader.h"
#include "world/terrain/terrain.h"
#include "world/client_world.h"
#include "network/client.h"
#include "ui/hud.h"
#include "player/settings/settings.h"

using namespace std;

int main() {
  Render* render = new Render();
  render->add_shader("flat", new Shader("src/shader/flat", true));
  render->add_shader("simple", new Shader("src/shader/simple", false));
  render->add_shader("line", new Shader("src/shader/line", false));

  SceneManager* scene_manager = new SceneManager();
  scene_manager->add("assets/player.glb");
  scene_manager->add("assets/missile.glb");
  scene_manager->load();

  Settings* settings = new Settings();
  Controller* controller = new Controller();
  settings->setup_controller(controller);

  Terrain* terrain = new Terrain(100);
  terrain->create_model();
  ClientWorld* world = new ClientWorld(terrain, false, scene_manager, render->particle_manager);
  render->world = world;

  world->force_physics_update();

  world->create_this_player(controller, render->camera);

  Client* client = new Client(world);

  // world_thread = thread(World::start_update_loop, this);
  // world_thread.detach();

  while (true) {
    client->process_response();
    world->update_controls();
    world->update();
    client->update_events(world->get_this_player(), render->camera->get_mouse_pressed());

    render->start(world->get_this_player());

    render->use("flat");
    render->render(terrain->instance);
    render->end();

    render->use("simple");
    Player* player;
    for (pair<uint, Player*> item : *world->players) {
      player = item.second;
      render->render(player->scene);
    }
    Projectile* projectile;
    for (pair<uint, Projectile*> item : *world->projectiles) {
      projectile = item.second;
      render->render(projectile->get_scene());
    }
    render->render(world->get_this_player()->scene);
    render->end();

    // render->use("line");
    // world->draw_debug();
    // render->end();

    render->finish();
  }
}
