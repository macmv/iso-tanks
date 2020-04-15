#include "angle-bar.h"
#include "ui/hud.h"

AngleBar::AngleBar(UIRender* render, sf::Color color, bool angle_right) : Drawable(render) {
  this->color = color;
  this->angle_right = angle_right;
}

void AngleBar::render(glm::vec2 position, glm::vec2 size) {
  float triangle_width = size.y * 0.4;
  float rectangle_width = size.x - triangle_width;
  if (angle_right) {
    ui_render->rectangle(position, glm::vec2(rectangle_width, size.y), color);
    ui_render->triangle(glm::vec2(position.x + rectangle_width, position.y),
        glm::vec2(position.x + rectangle_width, position.y + size.y),
        glm::vec2(position.x + size.x, position.y + size.y),
        color);
  } else {
    ui_render->rectangle(glm::vec2(position.x + triangle_width, position.y), glm::vec2(rectangle_width, size.y), color);
    ui_render->triangle(glm::vec2(position.x + triangle_width, position.y),
        glm::vec2(position.x + triangle_width, position.y + size.y),
        glm::vec2(position.x, position.y + size.y),
        color);
  }
}
