#include "section.h"
#include <SFML/Graphics.hpp>
#include <glm/gtx/string_cast.hpp>
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

void Section::add(Element* element) {
  elements->push_back(element);
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
  std::vector<Element*> firstElements = std::vector<Element*>();
  std::vector<Element*> lastElements = std::vector<Element*>();
  for (Element* element : *elements) {
    if (isVertical) {
      if (element->getTopShifted()) {
        firstElements.push_back(element);
      } else {
        lastElements.push_back(element);
      }
    } else {
      if (element->getLeftShifted()) {
        firstElements.push_back(element);
      } else {
        lastElements.push_back(element);
      }
    }
  }
  std::reverse(begin(lastElements), end(lastElements));
  glm::vec2 elementSize = glm::vec2();
  glm::vec2 elementPosition = glm::vec2();
  float minX = position.x;
  float minY = position.y;
  float maxX = position.x + size.x;
  float maxY = position.y + size.y;
  for (Element* element : firstElements) {
    elementSize = element->getSize();
    margin = element->getMargin();
    if (isVertical) {
      elementPosition.y = minY + margin;
      minY += elementSize.y + margin * 2;
      if (element->getLeftShifted()) {
        elementPosition.x = minX + margin;
      } else {
        elementPosition.x = maxX - elementSize.x - margin;
      }
    } else {
      elementPosition.x = minX + margin;
      minX += elementSize.x + margin * 2;
      if (element->getTopShifted()) {
        elementPosition.y = minY + margin;
      } else {
        elementPosition.y = maxY - elementSize.y - margin;
      }
    }
    element->render(elementPosition, elementSize);
  }
  minX = position.x;
  minY = position.y;
  maxX = position.x + size.x;
  maxY = position.y + size.y;
  for (Element* element : lastElements) {
    elementSize = element->getSize();
    margin = element->getMargin();
    if (isVertical) {
      maxY -= elementSize.y + margin * 2;
      elementPosition.y = maxY + margin;
      if (element->getLeftShifted()) {
        elementPosition.x = minX + margin;
      } else {
        elementPosition.x = maxX - elementSize.x - margin;
      }
    } else {
      maxX -= elementSize.x + margin * 2;
      elementPosition.x = maxX + margin;
      if (element->getTopShifted()) {
        elementPosition.y = minY + margin;
      } else {
        elementPosition.y = maxY - elementSize.y - margin;
      }
    }
    element->render(elementPosition, elementSize);
  }
  uiRender->debugRectangle(position, size);
}
