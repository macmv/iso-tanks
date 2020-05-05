#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "options.h"
#include <filesystem>
#include <json/json.h>
#include <unordered_map>
#include <string>

class Settings {
  private:
    std::unordered_map<std::string, RangeOption*> ranges;
    std::unordered_map<std::string, KeyOption*> keys;
    std::unordered_map<std::string, ButtonOption*> buttons;

  public:
    Settings();
    void load_defaults();
    void load();
    void save();
    void add_range(std::string name, RangeOption* option);
    void add_key(std::string name, KeyOption* option);
    void add_button(std::string name, ButtonOption* option);
    RangeOption* get_range(std::string name);
    KeyOption* get_key(std::string name);
    ButtonOption* get_button(std::string name);
  private:
    void read_settings(std::filesystem::path filename);
};

#endif
