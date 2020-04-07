#include "angle-bar.h"
#include "ui/hud.h"

AngleBar::AngleBar(UIRender* render, sf::Color color, bool angleRight) : Drawable(render) {
  this->color = color;
  this->angleRight = angleRight;
}

void AngleBar::render(glm::vec2 position, glm::vec2 size) {
  float triangle_width = size.y * 0.4;
  float rectangle_width = size.x - triangle_width;
  if (angleRight) {
    uiRender->rectangle(position, glm::vec2(rectangle_width, size.y), color);
    uiRender->triangle(glm::vec2(position.x + rectangle_width, position.y),
        glm::vec2(position.x + rectangle_width, position.y + size.y),
        glm::vec2(position.x + size.x, position.y + size.y),
        color);
  } else {
    uiRender->rectangle(glm::vec2(position.x + triangle_width, position.y), glm::vec2(rectangle_width, size.y), color);
    uiRender->triangle(glm::vec2(position.x + triangle_width, position.y),
        glm::vec2(position.x + triangle_width, position.y + size.y),
        glm::vec2(position.x, position.y + size.y),
        color);
  }
}
