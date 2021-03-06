#ifndef _HUD_H
#define _HUD_H

#include "player/controlled_player.h"
#include "opengl/render.h"

class Section;
class UIRender;

class Hud {
  private:
    Section* container;
  public:
    float scale;
    UIRender* ui_render;

  public:
    Hud(UIRender* render, float scale);
    void render(ControlledPlayer* player);
};

#endif
