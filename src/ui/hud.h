#ifndef _HUD_H
#define _HUD_H

#include "player/controlled_player.h"
#include "opengl/render.h"

class Section;

class Hud {
  private:
    ControlledPlayer* player;
    Section* container;
  public:
    UIRender* uiRender;

  public:
    Hud(UIRender* render, ControlledPlayer* player);
    void render();
};

#endif
