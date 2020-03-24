#include "text_render.h"
#include "render.h"
#include <SFML/Graphics/Font.hpp>

using namespace std;

TextRender::TextRender(Render* render, string name) {
  font = new sf::Font();
  if (!font->loadFromFile(name)) {
    cout << "Could not load " << name << " font!" << endl;
    exit(1);
  }
}

void TextRender::render(sf::Text* text) {

}
