#include <iostream>
#include "opengl/render.h"
#include "opengl/loader.h"
#include "world/terrain/terrain.h"

using namespace std;

int main() {
  World* world;
  Render* render = new Render(world);

  Terrain* terrain = new Terrain(10);

  while (true) {
    render->update(terrain->instance);
  }
}
