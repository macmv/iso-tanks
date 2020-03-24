#ifndef _HUD_H
#define _HUD_H

#include "player/controlled_player.h"
#include "opengl/render.h"

class Hud {
  private:
    ControlledPlayer* player;

  public:
    Hud(ControlledPlayer* player);
    void render(Render* render);
};

#endif
