#include "element.h"
#include "ui/position.h"
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

Element::Element(Hud* container, Position* position) : hud(container) {
  this->position = position;
}

Position Element::getPosition() {
  return *position;
}

