#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "actions.h"
#include "options.h"
#include <string>
#include <unordered_map>

class Controller {
  private:
    std::unordered_map<std::string, KeyAction*> key_actions;
    std::unordered_map<std::string, MouseButtonAction*> mouse_button_actions;

  public:
    void add(std::string name, KeyOption* option);
    void add(std::string name, ButtonOption* option);
    bool is_action_pressed(std::string name);
  private:
    bool has_action(std::string name);
};

#endif
