#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <SFML/Graphics.hpp>

class Display {
  public:
    sf::RenderWindow* window;

  public:
    Display();
    void init();
    void create_window();
    bool update();
    void reset_mouse();
    sf::Vector2u get_window_size();
    sf::Vector2i get_center();
    void render();
    void close();
};

#endif
