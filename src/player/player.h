#ifndef _PLAYER_H
#define _PLAYER_H

#include <bullet/btBulletDynamicsCommon.h>
#include "models/scene.h"

class Player {
  protected:
    btRigidBody* body;
    float turret_angle = 0;
    int health;
  public:
    Scene* scene;

  public:
    Player(btRigidBody* body);
    void update();
    glm::mat4 get_transform();
    void set_transform(glm::mat4 transform);
    void set_gravity(glm::vec3 gravity);
};

#endif
