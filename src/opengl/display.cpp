#include "display.h"
#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

Display::Display() {
  init();
  createWindow();
}

void Display::init() {
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    cout << "Could not initialize glew" << endl;
  }
}

void Display::createWindow() {
  glEnable(GL_TEXTURE_2D);

  cout << "Creating window" << endl;

  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 2;
  settings.majorVersion = 3;
  settings.minorVersion = 2;

  window = new Window(sf::VideoMode(800, 600), "Iso Tanks", sf::Style::Default, settings);
  window->setVerticalSyncEnabled(true);

  window->setActive(true);
}
