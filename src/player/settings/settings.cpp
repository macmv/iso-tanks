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
  write_settings(FileUtils::get_game_dir() / "settings.json");
}

void Settings::read_settings(filesystem::path filename) {
  if (filesystem::exists(filename)) {
    ifstream file(filename);
    Json::Value data;
    file >> data;
    file.close();
    for (Json::Value setting : data["settings"]["keys"]) {
      keys.insert({setting["name"].asString(), new KeyOption(setting["value"])});
    }
    for (Json::Value setting : data["settings"]["buttons"]) {
      buttons.insert({setting["name"].asString(), new ButtonOption(setting["value"])});
    }
    for (Json::Value setting : data["settings"]["ranges"]) {
      ranges.insert({setting["name"].asString(), new RangeOption(setting["value"])});
    }
  } else {
    throw filename.string() + " does not exist!";
  }
}

void Settings::write_settings(filesystem::path filename) {
  Json::Value keys;
  for (pair<string, KeyOption*> option : this->keys) {
    Json::Value obj;
    obj["name"] = option.first;
    obj["value"] = option.second->to_json();
    keys.append(obj);
  }
  Json::Value buttons;
  for (pair<string, ButtonOption*> option : this->buttons) {
    Json::Value obj;
    obj["name"] = option.first;
    obj["value"] = option.second->to_json();
    buttons.append(obj);
  }
  Json::Value ranges;
  for (pair<string, RangeOption*> option : this->ranges) {
    Json::Value obj;
    obj["name"] = option.first;
    obj["value"] = option.second->to_json();
    ranges.append(obj);
  }
  Json::Value settings;
  settings["keys"] = keys;
  settings["buttons"] = buttons;
  settings["ranges"] = ranges;
  Json::Value data;
  data["settings"] = settings;
  Json::StreamWriterBuilder builder;
  builder["commentStyle"] = "None";
  builder["indentation"] = "";
  std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
  ofstream file(filename);
  writer->write(data, &file);
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
