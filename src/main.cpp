#include <iostream>
#include "opengl/render.h"
#include "opengl/loader.h"
#include "world/terrain/terrain.h"
#include "world/world.h"

using namespace std;

int main() {
  World* world = new World();
  Render* render = new Render(world);

  Terrain* terrain = new Terrain(100);

  while (true) {
    render->update(terrain->instance);
  }
}
