#ifndef _PLAYER_H
#define _PLAYER_H

#include <bullet/btBulletDynamicsCommon.h>
#include "models/scene.h"

class Player {
  protected:
    btRigidBody* body;
    float turretAngle = 0;
  public:
    Scene* scene;

  public:
    Player(btRigidBody* body);
    glm::mat4 getTransform();
    void setGravity(glm::vec3 gravity);
};

#endif
