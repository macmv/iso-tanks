#include "controller.h"

using namespace std;

void Controller::add(string name, KeyOption* option) {
  if (has_action(name)) {
    cerr << "Cannot add action " << name << ", as another action exists with the same name!" << endl;
    return;
  }
  key_actions.insert({name, new KeyAction(option->get_key())});
}

void Controller::add(string name, ButtonOption* option) {
  if (has_action(name)) {
    cerr << "Cannot add action " << name << ", as another action exists with the same name!" << endl;
    return;
  }
  mouse_button_actions.insert({name, new MouseButtonAction(option->get_button())});
}

bool Controller::is_action_pressed(string name) {
  unordered_map<string, KeyAction*>::iterator key_action = key_actions.find(name);
  if (key_action != key_actions.end()) {
    return key_action->second->is_pressed();
  }
  unordered_map<string, MouseButtonAction*>::iterator mouse_button_action = mouse_button_actions.find(name);
  if (mouse_button_action != mouse_button_actions.end()) {
    return mouse_button_action->second->is_pressed();
  }
  cerr << "Cannot find action " << name << endl;
  return false;
}

bool Controller::has_action(string name) {
  if (key_actions.find(name) == key_actions.end() &&
      mouse_button_actions.find(name) == mouse_button_actions.end()) {
    return false;
  } else {
    return true;
  }
}
