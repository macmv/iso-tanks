#include "hud.h"
#include "player/player.h"
#include "opengl/render.h"

Hud::Hud(ControlledPlayer* player) {
  this->player = player;
}

void Hud::render(Render* render) {
  render->textRender->start();
  render->textRender->render(render->textRender->createText("reee"));
  render->textRender->end();
}
