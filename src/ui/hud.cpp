#include "hud.h"
#include "player/player.h"
#include "opengl/render.h"
#include "section.h"
#include "text.h"

Hud::Hud(UIRender* render, ControlledPlayer* player) {
  this->player = player;
  uiRender = render;
  container = new Section(this, false, true, true);
  Section* health = new Section(this, true, true, false);
  health->add(new Text(this, "Health", true, false));
  health->add(new Text(this, "<Health Slider Here>", true, false));
  container->add(health);
  container->add(new Text(this, "GAMER 2", true, false));
}

void Hud::render() {
  uiRender->start();
  container->render(glm::vec2(0, 0), uiRender->size());
  uiRender->end();
}
