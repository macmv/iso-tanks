#include <iostream>
#include "opengl/render.h"
#include "opengl/loader.h"
#include "opengl/shader.h"
#include "world/terrain/terrain.h"
#include "world/world.h"
#include "network/client.h"
#include "ui/hud.h"

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

  Terrain* terrain = new Terrain(100);
  terrain->create_model();
  World* world = new World(terrain, true, scene_manager);
  render->world = world;

  world->create_this_player(render->camera);

  Client* client = new Client(world);

  while (true) {
    client->process_response();
    world->update_controls(render->camera->get_mouse_delta().x);
    world->update();
    client->update_events(world->get_this_player(), render->camera->get_mouse_pressed());

    render->start(world->get_this_player());

    render->use("flat");
    render->render(terrain->instance);
    render->end();

    render->use("simple");
    Player* player;
    for (std::pair<int, Player*> pair : *world->players) {
      player = pair.second;
      render->render(player->scene);
    }
    render->render(world->get_this_player()->scene);
    render->end();

    // render->use("line");
    // world->draw_debug();
    // render->end();

    render->update();
  }
  world->clean();
}
