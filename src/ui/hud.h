#ifndef _HUD_H
#define _HUD_H

#include "player/controlled_player.h"
#include "opengl/render.h"

class Section;

class Hud {
  private:
    Section* container;
  public:
    float scale;
    UIRender* uiRender;

  public:
    Hud(UIRender* render, float scale);
    void render(ControlledPlayer* player);
};

#endif
