#ifndef _SECTION_H
#define _SECTION_H

#include "element.h"
#include <vector>
#include "opengl/ui_render.h"

class Section : public Element {
  private:
    std::vector<Element*>* elements = new std::vector<Element*>();
    bool is_vertical;
    UIRender* ui_render;

  public:
    Section(Hud* hud, Position* position, bool isVertical);
    glm::vec2 get_size();
    float get_margin();
    void render(glm::vec2 position, glm::vec2 size);
    void add(Element* element);
};

#endif
