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
  return text;
}

void UIRender::debugRectangle(glm::vec2 position, glm::vec2 size) {
  sf::RectangleShape shape(sf::Vector2f(size.x, size.y));
  shape.setFillColor(sf::Color::Transparent);
  shape.setOutlineThickness(1);
  shape.setOutlineColor(sf::Color(255, 0, 0));
  shape.setPosition(position.x, position.y);
  window->draw(shape);
}

void UIRender::rectangle(glm::vec2 position, glm::vec2 size, sf::Color color) {
  sf::RectangleShape shape(sf::Vector2f(size.x, size.y));
  shape.setFillColor(color);
  shape.setPosition(position.x, position.y);
  window->draw(shape);
}

void UIRender::triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, sf::Color color) {
  sf::ConvexShape shape;
  shape.setPointCount(3);
  shape.setPoint(0, sf::Vector2f(a.x, a.y));
  shape.setPoint(1, sf::Vector2f(b.x, b.y));
  shape.setPoint(2, sf::Vector2f(c.x, c.y));
  shape.setFillColor(color);
  window->draw(shape);
}

glm::vec2 UIRender::size() {
  sf::Vector2u size = window->getSize();
  return glm::vec2(size.x, size.y);
}
