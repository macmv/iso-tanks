#ifndef _PLAYER_H
#define _PLAYER_H

#include <bullet/btBulletDynamicsCommon.h>
#include "network/client.h"
#include "models/scene.h"

class Client;

class Player {
  public:
    btRigidBody* body;
    Scene* scene;
    float turretAngle = 0;
    Client* client;

  public:
    Player(btRigidBody* body);
    void update(float mouseDelta);
    glm::mat4 getTransform();
};

#endif
