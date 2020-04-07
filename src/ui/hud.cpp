#include "hud.h"
#include "player/player.h"
#include "opengl/render.h"
#include "element/section.h"
#include "element/text.h"
#include "element/slider.h"
#include "drawable/rectangle.h"
#include "drawable/angle-bar.h"
#include <SFML/Graphics.hpp>

Hud::Hud(UIRender* render, float scale) {
  this->scale = scale;
  uiRender = render;
  Section* health = new Section(this, new Position(true, false), true);
  health->add(new Text(this, new Position(true, false), "Health"));
  health->add(new Slider(this, new Position(true, false),
        0, 100, 75, true,
        new AngleBar(uiRender, sf::Color::Red, true),
        new AngleBar(uiRender, sf::Color::Black, true)));
  Section* ammo = new Section(this, new Position(false, false), true);
  ammo->add(new Text(this, new Position(false, false), "Ammo"));
  ammo->add(new Slider(this, new Position(false, false),
        0, 100, 75, false,
        new AngleBar(uiRender, sf::Color::Yellow, false),
        new AngleBar(uiRender, sf::Color::Black, false)));
  container = new Section(this, new Position(true, true), false);
  container->add(health);
  container->add(ammo);
}

void Hud::render(ControlledPlayer* player) {
  uiRender->start();
  container->render(glm::vec2(0, 0), uiRender->size());
  uiRender->end();
}
