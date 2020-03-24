#include "text.h"
#include <SFML/Graphics.hpp>

Text::Text(Hud* hud, string text) : Element(hud) {
  uiRender = hud->uiRender;
  this->text = uiRender->createText(text);
}

glm::vec2 Text::getPosition() {
  return glm::vec2(0, 0);
}

glm::vec2 Text::getSize() {
  return glm::vec2(0.1, 0.1);
}

void Text::render(glm::vec2 position, glm::vec2 size) {
  uiRender->render(text);
}

