#ifndef _TEXT_H
#define _TEXT_H

#include <SFML/Graphics.hpp>
#include "ui/hud.h"
#include "element.h"

using namespace std;

class Hud;

class Text : public Element {
  private:
    UIRender* ui_render;
    sf::Text* text;

  public:
    Text(Hud* hud, Position* position, string text);
    glm::vec2 get_size();
    float get_margin();
    void render(glm::vec2 position, glm::vec2 size);
};

#endif
