#ifndef _TEXT_H
#define _TEXT_H

#include <SFML/Graphics.hpp>
#include "ui/hud.h"
#include "element.h"

using namespace std;

class Hud;

class Text : public Element {
  private:
    UIRender* uiRender;
    sf::Text* text;

  public:
    Text(Hud* hud, Position* position, string text);
    glm::vec2 getSize();
    float getMargin();
    void render(glm::vec2 position, glm::vec2 size);
};

#endif
