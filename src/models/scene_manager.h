#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include "scene.h"
#include <unordered_map>

using namespace std;

class SceneManager {
  private:
    std::unordered_map<string, Scene*> scenes;

  public:
    SceneManager();
    void add(string name);
    void load();
    Scene* new_instance(string name);
};

#endif
