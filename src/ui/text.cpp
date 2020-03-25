#include "text.h"
#include <SFML/Graphics.hpp>

Text::Text(Hud* hud, string text, bool isLeftShifted, bool isTopShifted) : Element(hud) {
  uiRender = hud->uiRender;
  this->text = uiRender->createText(text);
  this->isLeftShifted = isLeftShifted;
  this->isTopShifted = isTopShifted;
}

bool Text::getLeftShifted() {
  return isLeftShifted;
}

bool Text::getTopShifted() {
  return isTopShifted;
}

float Text::getMargin() {
  return 10;
}

glm::vec2 Text::getSize() {
  return glm::vec2(text->getLocalBounds().width, text->getLocalBounds().height);
}

void Text::render(glm::vec2 position, glm::vec2 size) {
  uiRender->debugRectangle(position, size);
  text->setPosition(position.x, position.y);
  uiRender->render(text);
}

