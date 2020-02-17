#include <iostream>
#include "opengl/render.h"
#include "opengl/loader.h"
#include "models/model.h"

using namespace std;

int main() {
  World* world;
  Render* render = new Render(world);

  Model* model = new Model();
  loadModel("assets/test.obj", model);

  while (true) {
    render->update(model);
  }
}
