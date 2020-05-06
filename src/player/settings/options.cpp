#include "options.h"
#include <json/json.h>

KeyOption::KeyOption(Json::Value json) {
  this->key = static_cast<sf::Keyboard::Key>(json["key"].asInt());
}

Json::Value KeyOption::to_json() {
  Json::Value obj;
  obj["key"] = key;
  return obj;
}

ButtonOption::ButtonOption(Json::Value json) {
  this->button = static_cast<sf::Mouse::Button>(json["button"].asInt());
}

Json::Value ButtonOption::to_json() {
  Json::Value obj;
  obj["button"] = button;
  return obj;
}

RangeOption::RangeOption(Json::Value json) {
  this->min = json["min"].asFloat();
  this->max = json["max"].asFloat();
  this->value = json["value"].asFloat();
}

Json::Value RangeOption::to_json() {
  Json::Value obj;
  obj["min"] = min;
  obj["max"] = max;
  obj["value"] = value;
  return obj;
}
