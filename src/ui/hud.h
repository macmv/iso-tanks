#ifndef _HUD_H
#define _HUD_H

#include "player/controlled_player.h"
#include "opengl/render.h"
#include "text.h"

class Text;

class Hud {
  private:
    ControlledPlayer* player;
    Text* container;
  public:
    UIRender* uiRender;

  public:
    Hud(UIRender* render, ControlledPlayer* player);
    void render();
};

#endif
