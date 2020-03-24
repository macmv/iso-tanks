#include "section.h"
#include <SFML/Graphics.hpp>
#include "hud.h"

Section::Section(Hud* hud, bool isVertical) : Element(hud) {
  this->isVertical = isVertical;
  uiRender = hud->uiRender;
}

bool Section::getLeftShifted() {
  return true;
}

bool Section::getTopShifted() {
  return true;
}

float Section::getMargin() {
  return 10;
}

glm::vec2 Section::getSize() {
  float width = 0;
  float height = 0;
  for (Element* e : *elements) {
    glm::vec2 size = e->getSize();
    float margin = e->getMargin();
    if (isVertical) {
      height += size.y + margin * 2;
      if (size.x > width) {
        width = size.x;
      }
    } else {
      width += size.x + margin * 2;
      if (size.y > height) {
        height = size.y;
      }
    }
  }
  return glm::vec2(width, height);
}

void Section::render(glm::vec2 position, glm::vec2 size) {
  float minX = position.x;
  float minY = position.y;
  float maxX = position.x + size.x;
  float maxY = position.y + size.y;
  for (Element* element : *elements) {
    glm::vec2 elementSize = element->getSize();
    bool leftShifted = element->getLeftShifted();
    bool topShifted = element->getTopShifted();
    float margin = element->getMargin();
    glm::vec2 elementPosition = glm::vec2();
    if (isVertical) {
      if (topShifted) {
        elementPosition.y = minY + margin;
        minY += elementSize.y + margin * 2;
      } else {
        maxY -= elementSize.y + margin * 2;
        elementPosition.y = maxY + margin;
      }
      if (leftShifted) {
        elementPosition.x = minX + margin;
      } else {
        elementPosition.x = maxX - elementSize.x - margin;
      }
    } else {
      if (leftShifted) {
        elementPosition.x = minX + margin;
        minX += elementSize.x + margin * 2;
      } else {
        maxX -= elementSize.x + margin * 2;
        elementPosition.x = maxX + margin;
      }
      if (topShifted) {
        elementPosition.y = maxY - elementSize.y - margin;
      } else {
        elementPosition.y = minY + margin;
      }
    }
    element->render(elementPosition, elementSize);
  }
  uiRender->debugRectangle(position, size);
}
