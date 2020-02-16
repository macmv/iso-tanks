#include <iostream>
#include "opengl/render.h"

using namespace std;

int main() {
  World* world;
  Render* render = new Render(world);

  while (true) {
    render->update();
  }
}
