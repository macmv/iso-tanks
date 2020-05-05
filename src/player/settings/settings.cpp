#include "settings.h"
#include <json/json.h>
#include <iostream>
#include <string>
#include <fstream>
#include "options.h"
#include "system/file_utils.h"

using namespace std;

Settings::Settings() {
}

void Settings::load_defaults() {
  read_settings(FileUtils::get_game_dir() / "default_settings.json");
}

void Settings::load() {
  read_settings(FileUtils::get_game_dir() / "settings.json");
}

void Settings::save() {
  throw "Cannot save settings yet!";
}

void Settings::read_settings(filesystem::path filename) {
  if (filesystem::exists(filename)) {
    ifstream file(filename);
    Json::Value data;
    file >> data;
    for (Json::Value setting : data["settings"]["keys"]) {
      keys.insert({setting["name"].asString(), new KeyOption(static_cast<sf::Keyboard::Key>(setting["value"].asInt()))});
    }
  } else {
    throw filename.string() + " does not exist!";
  }
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
