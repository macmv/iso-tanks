#ifndef _SECTION_H
#define _SECTION_H

#include "element.h"
#include <vector>
#include "opengl/ui_render.h"

class Section : public Element {
  private:
    std::vector<Element*>* elements = new std::vector<Element*>();
    bool isVertical;
    UIRender* uiRender;

  public:
    Section(Hud* hud, bool isVertical);
    glm::vec2 getSize();
    bool getLeftShifted();
    bool getTopShifted();
    float getMargin();
    void render(glm::vec2 position, glm::vec2 size);
    void add(Element* element);
};

#endif
