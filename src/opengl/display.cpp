#include "display.h"
#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

Display::Display() {
  createWindow();
  init();
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

  window->setFramerateLimit(60);
}

bool Display::update() {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      // end the program
      return false;
    } else if (event.type == sf::Event::Resized) {
      // adjust the viewport when the window is resized
      glViewport(0, 0, event.size.width, event.size.height);
    }
  }
  return true;
}

void Display::render() {
  window->display();
}
