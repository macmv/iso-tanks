#ifndef _TEXT_RENDER_H
#define _TEXT_RENDER_H
#include "render.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class TextRender {
  private:
    sf::Font* font;
    sf::RenderWindow* window;

  public:
    TextRender(Render* render, string font);
    void start();
    void end();
    void render(sf::Text* text);
    sf::Text* createText(string words);
};

#endif