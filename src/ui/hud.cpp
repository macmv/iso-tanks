#include "hud.h"
#include "player/player.h"
#include "opengl/render.h"
#include "section.h"
#include "text.h"

Hud::Hud(UIRender* render, ControlledPlayer* player) {
  this->player = player;
  uiRender = render;
  container = new Section(this, true);
  container->add(new Text(this, "GAMER"));
}

void Hud::render() {
  uiRender->start();
  container->render(glm::vec2(1000, 1000), glm::vec2(1920, 1080));
  uiRender->end();
}
