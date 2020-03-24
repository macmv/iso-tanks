#include "text.h"
#include <SFML/Graphics.hpp>

Text::Text(Hud* hud, string text) : Element(hud) {
  uiRender = hud->uiRender;
  this->text = uiRender->createText(text);
}

bool Text::getLeftShifted() {
  return true;
}

bool Text::getTopShifted() {
  return false;
}

float getMargin() {
  return 10;
}

glm::vec2 Text::getSize() {
  return glm::vec2(100, 30);
}

void Text::render(glm::vec2 position, glm::vec2 size) {
  uiRender->render(text);
}

