#ifndef _OPTION_H
#define _OPTION_H

#include <string>
#include <SFML/Window.hpp>
#include <json/json.h>

class Option {
  private:
    std::string name;

  public:
    virtual Json::Value to_json() = 0;
};

class KeyOption : public Option {
  private:
    sf::Keyboard::Key key;

  public:
    KeyOption(Json::Value json);
    Json::Value to_json();
};

class ButtonOption : public Option {
  private:
    sf::Mouse::Button button;

  public:
    ButtonOption(Json::Value json);
    Json::Value to_json();
};

class RangeOption : public Option {
  private:
    float min;
    float max;
    float value;

  public:
    RangeOption(Json::Value json);
    Json::Value to_json();
};

#endif
