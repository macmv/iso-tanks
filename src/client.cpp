#include <iostream>
#include "opengl/render.h"
#include "opengl/loader.h"
#include "opengl/shader.h"
#include "world/terrain/terrain.h"
#include "world/world.h"

using namespace std;

int main() {
  Render* render = new Render();
  render->add_shader("flat", new Shader("src/shader/flat", true));
  render->add_shader("simple", new Shader("src/shader/simple", false));
  render->add_shader("line", new Shader("src/shader/line", false));

  Terrain* terrain = new Terrain(100);
  World* world = new World(terrain);
  render->world = world;

  world->add_player();

  while (true) {
    world->updateControls(render->camera->getMouseDelta().x);
    world->update();

    render->start(world->getPlayer());

    render->use("flat");
    render->render(terrain->instance);
    render->end();
    render->use("simple");
    for (Player* player : *world->players) {
      render->render(player->scene);
    }
    render->end();
    // render->use("line");
    // world->drawDebug();
    // render->end();

    render->update();
  }
  world->clean();
}
