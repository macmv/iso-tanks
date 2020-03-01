#ifndef _PLAYER_H
#define _PLAYER_H

#include <bullet/btBulletDynamicsCommon.h>
#include "../models/scene.h"

class Player {
  public:
    btRigidBody* body;
    Scene* scene;

  public:
    Player(btRigidBody* body);
    void update();
    glm::mat4 getTransform();
};

#endif
