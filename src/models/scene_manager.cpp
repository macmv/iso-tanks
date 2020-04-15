#include "scene_manager.h"
#include <unordered_map>
#include "opengl/loader.h"
#include <iostream>

using namespace std;

SceneManager::SceneManager() {
}

void SceneManager::add(string name) {
  Scene* scene = new Scene();
  scenes.insert({ name, scene });
}

void SceneManager::load() {
  for (pair<string, Scene*> item : scenes) {
    Loader::load_scene(item.first, item.second);
  };
}

Scene* SceneManager::new_instance(string name) {
  Scene* scene = scenes.at(name);
  return scene->new_instance();
}
