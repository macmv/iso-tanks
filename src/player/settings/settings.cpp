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
  try {
    cout << "Loading settings from settings.cfg" << endl;
    load();
  } catch (string e) {
    cout << "Could not load settings, loading defaults" << endl;
    load_defaults();
  }
}

void Settings::load_defaults() {
  keys.clear();
  keys.insert({"forward", new KeyOption(sf::Keyboard::Key::W)});
  keys.insert({"backward", new KeyOption(sf::Keyboard::Key::S)});
  keys.insert({"left", new KeyOption(sf::Keyboard::Key::A)});
  keys.insert({"right", new KeyOption(sf::Keyboard::Key::D)});
  buttons.clear();
  buttons.insert({"fire", new ButtonOption(sf::Mouse::Button::Left)});
  ranges.clear();
}

void Settings::load() {
  read_settings(FileUtils::get_game_dir() / "settings.cfg");
}

void Settings::save() {
  write_settings(FileUtils::get_game_dir() / "settings.cfg");
}

void Settings::setup_controller(Controller* controller) {
  controller->add("forward", keys.at("forward"));
  controller->add("backward", keys.at("backward"));
  controller->add("left", keys.at("left"));
  controller->add("right", keys.at("right"));
}

void Settings::read_settings(filesystem::path filename) {
  if (filesystem::exists(filename)) {
    SettingsProto proto;
    ifstream file(filename);
    proto.ParseFromIstream(&file);
    file.close();
    cout << "Loaded settings" << endl << proto.DebugString() << endl;
    for (SettingsProto::Key key : proto.keys()) {
      keys.insert({key.name(), new KeyOption(key)});
    }
    for (SettingsProto::Button button : proto.buttons()) {
      buttons.insert({button.name(), new ButtonOption(button)});
    }
    for (SettingsProto::Range range : proto.ranges()) {
      ranges.insert({range.name(), new RangeOption(range)});
    }
  } else {
    cerr << filename.string() + " does not exist!" << endl;
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
