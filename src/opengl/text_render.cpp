#include "text_render.h"
#include "render.h"
#include <SFML/Graphics.hpp>

using namespace std;

TextRender::TextRender(Render* render, string name) {
  font = new sf::Font();
  if (!font->loadFromFile(name)) {
    cout << "Could not load " << name << " font!" << endl;
    exit(1);
  }
  window = render->display->window;
}

void TextRender::start() {
  window->pushGLStates();
}

void TextRender::end() {
  window->popGLStates();
}

void TextRender::render(sf::Text* text) {
  window->draw(*text);
}

sf::Text* TextRender::createText(string words) {
  sf::Text* text = new sf::Text();
  text->setFont(*font);
  text->setString(words);
  text->setCharacterSize(24);
  text->setFillColor(sf::Color::Red);
  text->setStyle(sf::Text::Bold);
  text->move(100.f, 200.f);
  return text;
}
