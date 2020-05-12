#ifndef _PLAYER_H
#define _PLAYER_H

#include "models/scene_manager.h"
#include <reactphysics3d.h>

class Player {
  protected:
    rp3d::RigidBody* body;
    int health;
    glm::mat4 transform;
  public:
    float turret_angle = 0;
    Scene* scene;

  public:
    Player(rp3d::RigidBody* body, SceneManager* scene_manager);
    void update();
    glm::mat4 get_transform();
    void set_transform(glm::mat4 transform);
    void set_gravity(glm::vec3 gravity);
    void damage(int amount);
};

#endif
