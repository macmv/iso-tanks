#ifndef _DRAWABLE_H
#define _DRAWABLE_H

#include <glm/glm.hpp>
#include "ui/hud.h"

class Drawable {
  protected:
    UIRender* ui_render;

  public:
    Drawable(UIRender* render);
    virtual void render(glm::vec2 position, glm::vec2 size) = 0;
};

#endif
