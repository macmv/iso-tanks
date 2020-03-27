#include "hud.h"
#include "player/player.h"
#include "opengl/render.h"
#include "section.h"
#include "text.h"

Hud::Hud(UIRender* render, ControlledPlayer* player) {
  this->player = player;
  uiRender = render;
  Section* health = new Section(this, new Position(true, false), true);
  health->add(new Text(this, new Position(true, false), "Health"));
  health->add(new Text(this, new Position(true, false), "Health slider"));
  container = new Section(this, new Position(true, true), false);
  container->add(health);
  container->add(new Text(this, new Position(true, false), "GAMER 2"));
}

void Hud::render() {
  uiRender->start();
  container->render(glm::vec2(0, 0), uiRender->size());
  uiRender->end();
}
