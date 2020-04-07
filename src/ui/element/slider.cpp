#include "slider.h"
#include "ui/hud.h"
#include <iostream>

using namespace std;

Slider::Slider(Hud* hud, Position* position, int min, int max, int value, bool onLeftSide, Drawable* foreground, Drawable* background) : Element(hud, position) {
  this->min = min;
  this->max = max;
  this->value = value;
  this->background = background;
  this->foreground = foreground;
  this->onLeftSide = onLeftSide;
}

float Slider::getMargin() {
  return 10;
}

glm::vec2 Slider::getSize() {
  return glm::vec2(max - min, 20);
}

void Slider::render(glm::vec2 position, glm::vec2 size) {
  float percent = (float) (value - min) / (max - min);
  if (onLeftSide) {
    background->render(position, size);
    foreground->render(position, glm::vec2(size.x * percent, size.y));
  } else {
    background->render(position, size);
    foreground->render(glm::vec2(position.x + size.x * (1 - percent), position.y), glm::vec2(size.x * percent, size.y));
  }
}
