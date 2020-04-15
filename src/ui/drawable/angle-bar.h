#ifndef _ANGLE_BAR_H
#define _ANGLE_BAR_H

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "ui/hud.h"
#include "drawable.h"

class AngleBar : public Drawable {
  private:
    sf::Color color;
    bool angle_right;

  public:
    AngleBar(UIRender* render, sf::Color color, bool angle_right);
    void render(glm::vec2 position, glm::vec2 size);
};

#endif
