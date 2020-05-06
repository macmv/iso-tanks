#ifndef _OPTION_H
#define _OPTION_H

#include <string>
#include <SFML/Window.hpp>
#include "src/proto/settings.pb.h"

class Option {
};

class KeyOption : public Option {
  private:
    sf::Keyboard::Key key;

  public:
    KeyOption(sf::Keyboard::Key key);
    KeyOption(SettingsProto::Key proto);
    void to_proto(SettingsProto::Key* proto);
    sf::Keyboard::Key get_key();
};

class ButtonOption : public Option {
  private:
    sf::Mouse::Button button;

  public:
    ButtonOption(sf::Mouse::Button button);
    ButtonOption(SettingsProto::Button proto);
    void to_proto(SettingsProto::Button* proto);
    sf::Mouse::Button get_button();
};

class RangeOption : public Option {
  private:
    float min;
    float max;
    float value;

  public:
    RangeOption(float min, float max, float value);
    RangeOption(SettingsProto::Range proto);
    void to_proto(SettingsProto::Range* proto);
    float get_value();
};

#endif
