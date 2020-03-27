#ifndef _SLIDER_H
#define _SLIDER_H

#include "ui/drawable/drawable.h"
#include "element.h"

class Slider : public Element {
  private:
    Drawable* background;
    Drawable* foreground;
    int max;
    int min;
    int value;

  public:
    Slider(Hud* hud, Position* position, int min, int max, int value, Drawable* foreground, Drawable* background);
    glm::vec2 getSize();
    float getMargin();
    void render(glm::vec2 position, glm::vec2 size);
};

#endif
