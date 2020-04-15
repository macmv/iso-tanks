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
    bool on_left_side;

  public:
    Slider(Hud* hud, Position* position, int min, int max, int value, bool on_left_side, Drawable* foreground, Drawable* background);
    glm::vec2 get_size();
    float get_margin();
    void render(glm::vec2 position, glm::vec2 size);
};

#endif
