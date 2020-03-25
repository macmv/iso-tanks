#ifndef _TEXT_H
#define _TEXT_H

#include <SFML/Graphics.hpp>
#include "hud.h"
#include "element.h"

using namespace std;

class Hud;

class Text : public Element {
  private:
    UIRender* uiRender;
    sf::Text* text;
    bool isLeftShifted;
    bool isTopShifted;

  public:
    Text(Hud* hud, string text, bool isLeftShifted, bool isTopShifted);
    bool getLeftShifted();
    bool getTopShifted();
    glm::vec2 getSize();
    float getMargin();
    void render(glm::vec2 position, glm::vec2 size);
};

#endif
