#include "controller.h"

using namespace std;

void Controller::add(string name, KeyOption* option) {
  key_actions.insert({name, new KeyAction(option->get_key())});
}

void Controller::add(string name, ButtonOption* option) {
  mouse_button_actions.insert({name, new MouseButtonAction(option->get_button())});
}
