#include "hud.h"
#include "player/player.h"
#include "opengl/render.h"
#include "element/section.h"
#include "element/text.h"
#include "element/slider.h"
#include "drawable/rectangle.h"
#include "drawable/angle-bar.h"
#include <SFML/Graphics.hpp>

Hud::Hud(UIRender* render, ControlledPlayer* player) {
  this->player = player;
  uiRender = render;
  Section* health = new Section(this, new Position(true, false), true);
  health->add(new Text(this, new Position(true, false), "Health"));
  health->add(new Slider(this, new Position(true, false), 0, 100, 75, new AngleBar(uiRender, sf::Color::Red), new AngleBar(uiRender, sf::Color::Black)));
  Section* ammo = new Section(this, new Position(false, false), true);
  ammo->add(new Text(this, new Position(false, false), "Ammo"));
  ammo->add(new Slider(this, new Position(false, false), 0, 100, 75, new AngleBar(uiRender, sf::Color::Yellow), new AngleBar(uiRender, sf::Color::Black)));
  container = new Section(this, new Position(true, true), false);
  container->add(health);
  container->add(ammo);
}

void Hud::render() {
  uiRender->start();
  container->render(glm::vec2(0, 0), uiRender->size());
  uiRender->end();
}
