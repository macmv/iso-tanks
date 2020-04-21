#ifndef _TEXT_RENDER_H
#define _TEXT_RENDER_H

#include "render.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Render;

using namespace std;

class UIRender {
  private:
    sf::Font* font;
    sf::RenderWindow* window;
    float font_size;

  public:
    UIRender(Render* render, string font, float fontSize);
    void start();
    void end();
    void render(sf::Text* text);
    sf::Text* create_text(string words, float scale);
    void debug_rectangle(glm::vec2 position, glm::vec2 size);
    void rectangle(glm::vec2 position, glm::vec2 size, sf::Color color);
    void triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, sf::Color color);
    glm::vec2 size();
};

#endif
