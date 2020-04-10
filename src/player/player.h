#ifndef _PLAYER_H
#define _PLAYER_H

#include <bullet/btBulletDynamicsCommon.h>
#include "models/scene.h"

class Player {
  protected:
    btRigidBody* body;
    float turretAngle = 0;
    int health;
  public:
    Scene* scene;

  public:
    Player(btRigidBody* body);
    void update();
    glm::mat4 getTransform();
    void setTransform(glm::mat4 transform);
    void setGravity(glm::vec3 gravity);
};

#endif
