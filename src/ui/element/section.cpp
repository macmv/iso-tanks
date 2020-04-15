#include "section.h"
#include <SFML/Graphics.hpp>
#include <glm/gtx/string_cast.hpp>
#include "ui/hud.h"

Section::Section(Hud* hud, Position* position, bool is_vertical) : Element(hud, position) {
  this->is_vertical = is_vertical;
  ui_render = hud->ui_render;
}

float Section::get_margin() {
  return 10;
}

void Section::add(Element* element) {
  elements->push_back(element);
}

glm::vec2 Section::get_size() {
  float width = 0;
  float height = 0;
  for (Element* e : *elements) {
    glm::vec2 size = e->get_size();
    float margin = e->get_margin();
    if (is_vertical) {
      height += size.y + margin * 2;
      if (size.x + margin * 2 > width) {
        width = size.x + margin * 2;
      }
    } else {
      width += size.x + margin * 2;
      if (size.y + margin * 2 > height) {
        height = size.y + margin * 2;
      }
    }
  }
  return glm::vec2(width, height);
}

void Section::render(glm::vec2 position, glm::vec2 size) {
  std::vector<Element*> first_elements = std::vector<Element*>();
  std::vector<Element*> last_elements = std::vector<Element*>();
  for (Element* element : *elements) {
    if (is_vertical) {
      if (element->get_position().top_shifted) {
        first_elements.push_back(element);
      } else {
        last_elements.push_back(element);
      }
    } else {
      if (element->get_position().left_shifted) {
        first_elements.push_back(element);
      } else {
        last_elements.push_back(element);
      }
    }
  }
  std::reverse(begin(last_elements), end(last_elements));
  glm::vec2 element_size = glm::vec2();
  glm::vec2 element_position = glm::vec2();
  float min_x = position.x;
  float min_y = position.y;
  float max_x = position.x + size.x;
  float max_y = position.y + size.y;
  for (Element* element : first_elements) {
    element_size = element->get_size();
    margin = element->get_margin();
    if (is_vertical) {
      element_position.y = min_y + margin;
      min_y += element_size.y + margin * 2;
      if (element->get_position().left_shifted) {
        element_position.x = min_x + margin;
      } else {
        element_position.x = max_x - element_size.x - margin;
      }
    } else {
      element_position.x = min_x + margin;
      min_x += element_size.x + margin * 2;
      if (element->get_position().top_shifted) {
        element_position.y = min_y + margin;
      } else {
        element_position.y = max_y - element_size.y - margin;
      }
    }
    element->render(element_position, element_size);
  }
  min_x = position.x;
  min_y = position.y;
  max_x = position.x + size.x;
  max_y = position.y + size.y;
  for (Element* element : last_elements) {
    element_size = element->get_size();
    margin = element->get_margin();
    if (is_vertical) {
      max_y -= element_size.y + margin * 2;
      element_position.y = max_y + margin;
      if (element->get_position().left_shifted) {
        element_position.x = min_x + margin;
      } else {
        element_position.x = max_x - element_size.x - margin;
      }
    } else {
      max_x -= element_size.x + margin * 2;
      element_position.x = max_x + margin;
      if (element->get_position().top_shifted) {
        element_position.y = min_y + margin;
      } else {
        element_position.y = max_y - element_size.y - margin;
      }
    }
    element->render(element_position, element_size);
  }
}
