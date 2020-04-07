#include "text.h"
#include <SFML/Graphics.hpp>

Text::Text(Hud* hud, Position* position, string text) : Element(hud, position) {
  uiRender = hud->uiRender;
  this->text = uiRender->createText(text);
}

float Text::getMargin() {
  return 10;
}

glm::vec2 Text::getSize() {
  return glm::vec2(text->getLocalBounds().width, text->getLocalBounds().height);
}

void Text::render(glm::vec2 position, glm::vec2 size) {
  text->setPosition(position.x, position.y);
  uiRender->render(text);
}

