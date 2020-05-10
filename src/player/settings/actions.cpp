#include "actions.h"

KeyAction::KeyAction(sf::Keyboard::Key key) {
  this->key = key;
}

bool KeyAction::is_pressed() {
  return sf::Keyboard::isKeyPressed(key);
}

MouseButtonAction::MouseButtonAction(sf::Mouse::Button button) {
  this->button = button;
}

bool MouseButtonAction::is_pressed() {
  return sf::Mouse::isButtonPressed(button);
}

JoystickButtonAction::JoystickButtonAction(uint joystick, uint button) {
  this->joystick = joystick;
  this->button = button;
}

bool JoystickButtonAction::is_pressed() {
  return sf::Joystick::isButtonPressed(joystick, button);
}
