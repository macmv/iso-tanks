#include "ui_render.h"
#include "render.h"
#include <SFML/Graphics.hpp>

using namespace std;

UIRender::UIRender(Render* render, string name) {
  font = new sf::Font();
  if (!font->loadFromFile(name)) {
    cout << "Could not load " << name << " font!" << endl;
    exit(1);
  }
  window = render->display->window;
}

void UIRender::start() {
  window->pushGLStates();
}

void UIRender::end() {
  window->popGLStates();
}

void UIRender::render(sf::Text* text) {
  window->draw(*text);
}

sf::Text* UIRender::createText(string words) {
  sf::Text* text = new sf::Text();
  text->setFont(*font);
  text->setString(words);
  text->setCharacterSize(24);
  text->setFillColor(sf::Color::Red);
  text->setStyle(sf::Text::Bold);
  text->move(100.f, 200.f);
  return text;
}
