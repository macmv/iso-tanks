#ifndef _TEXT_RENDER_H
#define _TEXT_RENDER_H
#include "render.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class UIRender {
  private:
    sf::Font* font;
    sf::RenderWindow* window;
    float fontSize;

  public:
    UIRender(Render* render, string font, float fontSize);
    void start();
    void end();
    void render(sf::Text* text);
    sf::Text* createText(string words, float scale);
    void debugRectangle(glm::vec2 position, glm::vec2 size);
    void rectangle(glm::vec2 position, glm::vec2 size, sf::Color color);
    void triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, sf::Color color);
    glm::vec2 size();
};

#endif
