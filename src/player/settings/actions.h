#ifndef _ACTIONS_H
#define _ACTIONS_H

#include <SFML/Window.hpp>

class Action {
};

class ToggleAction : Action {
  public:
    virtual bool is_pressed() = 0;
};

class VariableAction : Action {
  public:
    virtual float get_amount() = 0;
};

class KeyAction : ToggleAction {
  private:
    sf::Keyboard::Key key;

  public:
    KeyAction(sf::Keyboard::Key key);
    bool is_pressed();
};

class MouseButtonAction : ToggleAction {
  private:
    sf::Mouse::Button button;

  public:
    MouseButtonAction(sf::Mouse::Button button);
    bool is_pressed();
};

class JoystickButtonAction : ToggleAction {
  private:
    uint joystick;
    uint button;

  public:
    JoystickButtonAction(uint joystick, uint button);
    bool is_pressed();
};

#endif
