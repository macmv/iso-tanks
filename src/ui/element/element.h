#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <glm/glm.hpp>
#include "ui/position.h"

class Hud;

class Element {
  protected:
    float margin = 0;
    const Hud* hud;
    Position* position;
    float scale;

  public:
    Element(Hud* container, Position* position);
    virtual glm::vec2 get_size() = 0;
    virtual float get_margin() = 0;
    virtual void render(glm::vec2 position, glm::vec2 size) = 0;
    Position get_position();
};

#endif
