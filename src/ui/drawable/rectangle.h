#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "ui/hud.h"
#include "drawable.h"

class Rectangle : public Drawable {
  private:
    sf::Color color;

  public:
    Rectangle(UIRender* render, sf::Color color);
    void render(glm::vec2 position, glm::vec2 size);
};

#endif
