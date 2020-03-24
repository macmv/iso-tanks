#ifndef _TEXT_RENDER_H
#define _TEXT_RENDER_H
#include "render.h"
#include <iostream>
#include <SFML/Graphics/Font.hpp>

using namespace std;

class TextRender {
  private:
    sf::Font* font;

  public:
    TextRender(Render* render, string font);
    void render(sf::Text* text);
};

#endif
