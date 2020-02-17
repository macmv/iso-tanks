#include <SFML/Graphics.hpp>
#include "camera.h"

#ifndef _DISPLAY_H
#define _DISPLAY_H

class Display {
  private:
    sf::Window* window;

  public:
    Display();
    void init();
    void createWindow();
    bool update(Camera* camera);
    void render();
    void close();
};

#endif
