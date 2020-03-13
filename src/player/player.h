#ifndef _PLAYER_H
#define _PLAYER_H

#include <bullet/btBulletDynamicsCommon.h>
#include "models/scene.h"

class Player {
  public:
    btRigidBody* body;
    Scene* scene;
    float turretAngle = 0;

  public:
    Player(btRigidBody* body);
    void update(float mouseXDelta);
    glm::mat4 getTransform();
};

#endif
