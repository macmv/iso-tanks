#include "settings.h"
#include <json/json.h>
#include <iostream>
#include <string>
#include <fstream>
#include "options.h"
#include "system/file_utils.h"
#include "src/proto/settings.pb.h"

using namespace std;

Settings::Settings() {
}

void Settings::load_defaults() {
  read_settings(FileUtils::get_game_dir() / "default_settings.json");
}

void Settings::load() {
  read_settings(FileUtils::get_game_dir() / "settings.json");
}

void Settings::save_defaults() {
  keys.clear();
  keys.insert({"up", new KeyOption(sf::Keyboard::Key::W)});
  keys.insert({"down", new KeyOption(sf::Keyboard::Key::S)});
  keys.insert({"left", new KeyOption(sf::Keyboard::Key::A)});
  keys.insert({"right", new KeyOption(sf::Keyboard::Key::D)});
  buttons.clear();
  buttons.insert({"fire", new ButtonOption(sf::Mouse::Button::Left)});
  ranges.clear();
  write_settings(FileUtils::get_game_dir() / "default_settings.json");
}

void Settings::save() {
  write_settings(FileUtils::get_game_dir() / "settings.json");
}

void Settings::read_settings(filesystem::path filename) {
  if (filesystem::exists(filename)) {
    SettingsProto proto;
    ifstream file(filename);
    proto.ParseFromIstream(&file);
    file.close();
    cout << "Loaded settings" << endl << proto.DebugString() << endl;
  } else {
    throw filename.string() + " does not exist!";
  }
}

void Settings::write_settings(filesystem::path filename) {
  SettingsProto proto;
  SettingsProto::Key* key;
  for (pair<string, KeyOption*> option : keys) {
    key = proto.add_keys();
    key->set_name(option.first);
    option.second->to_proto(key);
  }
  SettingsProto::Button* button;
  for (pair<string, ButtonOption*> option : buttons) {
    button = proto.add_buttons();
    button->set_name(option.first);
    option.second->to_proto(button);
  }
  cout << "Writing protobuf: " << endl << proto.DebugString() << endl;
  ofstream file(filename);
  proto.SerializeToOstream(&file);
  file.close();
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
