#include "rectangle.h"
#include "ui/hud.h"

Rectangle::Rectangle(UIRender* render, sf::Color color) : Drawable(render) {
  this->color = color;
}

void Rectangle::render(glm::vec2 position, glm::vec2 size) {
  ui_render->rectangle(position, size, color);
}
