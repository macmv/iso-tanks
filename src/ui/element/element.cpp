#include "element.h"
#include "ui/position.h"
#include <glm/glm.hpp>
#include <iostream>
#include "ui/hud.h"

using namespace std;

Element::Element(Hud* container, Position* position) : hud(container) {
  this->position = position;
  this->scale = container->scale;
}

Position Element::get_position() {
  return *position;
}

