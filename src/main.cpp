#include <iostream>
#include "opengl/render.h"
#include "opengl/loader.h"
#include "world/terrain/terrain.h"
#include "world/world.h"

using namespace std;

int main() {
  Render* render = new Render();

  Terrain* terrain = new Terrain(100);
  World* world = new World(terrain);
  render->world = world;

  world->add_player();

  while (true) {
    world->update();
    render->start();
    render->render(terrain->instance);
    for (Player* player : *world->players) {
      render->render(player->instance);
    }
    render->end();
    render->update();
  }
}
