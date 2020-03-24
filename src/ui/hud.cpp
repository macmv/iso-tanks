#include "hud.h"
#include "player/player.h"
#include "opengl/render.h"
//#include "section.h"
#include "text.h"

Hud::Hud(UIRender* render, ControlledPlayer* player) {
  this->player = player;
  uiRender = render;
  // container = new Section(this, Section.Orientation.Horizontal);
  container = new Text(this, "GAMER");
}

void Hud::render() {
  uiRender->start();
  container->render(glm::vec2(0, 0), glm::vec2(1, 1));
  uiRender->end();
}
