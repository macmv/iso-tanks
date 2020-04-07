#include "angle-bar.h"
#include "ui/hud.h"

AngleBar::AngleBar(UIRender* render, sf::Color color) : Drawable(render) {
  this->color = color;
}

void AngleBar::render(glm::vec2 position, glm::vec2 size) {
  float rectangle_width = size.x - (size.y * 0.4);
  uiRender->rectangle(position, glm::vec2(rectangle_width, size.y), color);
  uiRender->triangle(glm::vec2(position.x + rectangle_width, position.y),
                     glm::vec2(position.x + rectangle_width, position.y + size.y),
                     glm::vec2(position.x + size.x, position.y + size.y),
                     color);
}
