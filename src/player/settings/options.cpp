#include "options.h"
#include "src/proto/settings.pb.h"

KeyOption::KeyOption(sf::Keyboard::Key key) {
  this->key = key;
}

KeyOption::KeyOption(SettingsProto::Key proto) {
}

void KeyOption::to_proto(SettingsProto::Key* proto) {
  proto->set_key(key);
}

sf::Keyboard::Key KeyOption::get_key() {
  return key;
}

ButtonOption::ButtonOption(sf::Mouse::Button button) {
  this->button = button;
}

ButtonOption::ButtonOption(SettingsProto::Button proto) {
}

void ButtonOption::to_proto(SettingsProto::Button* proto) {
  proto->set_button(button);
}

sf::Mouse::Button ButtonOption::get_button() {
  return button;
}

RangeOption::RangeOption(float min, float max, float value) {
  this->min = min;
  this->max = max;
  this->value = value;
}

RangeOption::RangeOption(SettingsProto::Range proto) {
}

void RangeOption::to_proto(SettingsProto::Range* proto) {
  proto->set_min(min);
  proto->set_max(max);
  proto->set_value(value);
}

float RangeOption::get_value() {
  return value;
}
