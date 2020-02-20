#ifndef _PLAYER_H
#define _PLAYER_H

#include "../models/model_instance.h"
#include <bullet/btBulletDynamicsCommon.h>

class Player {
  public:
    btRigidBody* body;
    ModelInstance* instance;

  public:
    Player(btRigidBody* body);
    void update();
};

#endif
