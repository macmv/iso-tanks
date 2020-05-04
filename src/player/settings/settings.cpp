#include "settings.h"
#include <iostream>
#include <string>
#include "options.h"
#include "system/file_utils.h"

using namespace std;

Settings::Settings() {
}

void Settings::load_defaults() {
  cout << FileUtils::get_game_dir() / "default_settings.json" << endl;
}

void Settings::load() {
  cout << FileUtils::get_game_dir() / "settings.json" << endl;
}

void Settings::save() {
  throw "Cannot save settings yet!";
}

void Settings::add_range(std::string name, RangeOption* option) {
  ranges.insert({name, option});
}

void Settings::add_key(std::string name, KeyOption* option) {
  keys.insert({name, option});
}

void Settings::add_button(std::string name, ButtonOption* option) {
  buttons.insert({name, option});
}

RangeOption* Settings::get_range(std::string name) {
  return ranges.at(name);
}

KeyOption* Settings::get_key(std::string name) {
  return keys.at(name);
}

ButtonOption* Settings::get_button(std::string name) {
  return buttons.at(name);
}
