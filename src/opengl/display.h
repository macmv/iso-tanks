#include <SFML/Graphics.hpp>

#ifndef _DISPLAY_H
#define _DISPLAY_H

class Display {
  private:
    sf::Window* window;

  public:
    Display();
    void init();
    void createWindow();
    bool update();
    void render();
};

#endif
