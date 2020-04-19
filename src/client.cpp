#include <iostream>
#include <glm/gtx/string_cast.hpp>
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

  ParticleCloud* test_particle = new ParticleCloud(10, 0.1f, 1, new Material(), "src/shader/circle_particle");
  test_particle->set_position(glm::vec3(0, -970, 0));

  while (true) {
    test_particle->update();
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
    for (pair<uint, Player*> item : *world->players) {
      player = item.second;
      render->render(player->scene);
    }
    Projectile* projectile;
    for (pair<uint, Projectile*> item : *world->projectiles) {
      projectile = item.second;
      // cout << "Rendering projectile at " << glm::to_string(projectile->get_scene()->transform) << endl;
      render->render(projectile->get_scene());
    }
    render->render(world->get_this_player()->scene);
    render->end();

    render->render(test_particle);

    // render->use("line");
    // world->draw_debug();
    // render->end();

    render->update();
  }
  world->clean();
}
