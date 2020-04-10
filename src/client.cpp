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

  Terrain* terrain = new Terrain(100);
  terrain->createModel();
  World* world = new World(terrain, true);
  render->world = world;

  world->createThisPlayer(render->camera);

  Client* client = new Client(world);

  while (true) {
    client->processResponse();
    world->updateControls(render->camera->getMouseDelta().x);
    world->update();
    client->updateEvents(world->getPlayer(), render->camera->getMousePressed());

    render->start(world->getPlayer());

    render->use("flat");
    render->render(terrain->instance);
    render->end();

    render->use("simple");
    Player* player;
    for (std::pair<int, Player*> pair : *world->players) {
      player = pair.second;
      render->render(player->scene);
    }
    render->render(world->getPlayer()->scene);
    render->end();

    // render->use("line");
    // world->drawDebug();
    // render->end();

    render->update();
  }
  world->clean();
}
