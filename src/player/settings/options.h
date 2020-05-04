#ifndef _OPTION_H
#define _OPTION_H

#include <string>
#include <SFML/Window.hpp>

class Option {
  private:
    std::string name;
};

class RangeOption : public Option {
  private:
    float min;
    float max;
    float value;
};

class KeyOption : public Option {
  private:
    sf::Keyboard::Key key;
};

class ButtonOption : public Option {
  private:
    sf::Mouse::Button button;
};

#endif
