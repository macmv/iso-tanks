#ifndef _TEXT_H
#define _TEXT_H

#include <SFML/Graphics.hpp>
#include "hud.h"
#include "element.h"

using namespace std;

class Hud;

class Text : Element {
  private:
    UIRender* uiRender;
    sf::Text* text;

  public:
    Text(Hud* hud, string text);
    bool getLeftShifted();
    bool getTopShifted();
    glm::vec2 getSize();
    float getMargin();
    void render(glm::vec2 position, glm::vec2 size);
};

#endif
