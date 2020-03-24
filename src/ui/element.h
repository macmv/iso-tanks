#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <glm/glm.hpp>

class Hud;

class Element {
  protected:
    float margin = 0;
    const Hud* hud;

  public:
    Element(Hud* container);
    virtual bool getLeftShifted() = 0;
    virtual bool getTopShifted() = 0;
    virtual glm::vec2 getSize() = 0;
    virtual float getMargin() = 0;
    virtual void render(glm::vec2 position, glm::vec2 size) = 0;
};

#endif
