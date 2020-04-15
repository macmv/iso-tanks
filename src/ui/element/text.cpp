#include "text.h"
#include <SFML/Graphics.hpp>

Text::Text(Hud* hud, Position* position, string text) : Element(hud, position) {
  ui_render = hud->ui_render;
  this->text = ui_render->create_text(text, scale);
}

float Text::get_margin() {
  return 10;
}

glm::vec2 Text::get_size() {
  return glm::vec2(text->getLocalBounds().width, text->getLocalBounds().height);
}

void Text::render(glm::vec2 position, glm::vec2 size) {
  text->setPosition(position.x, position.y);
  ui_render->render(text);
}

