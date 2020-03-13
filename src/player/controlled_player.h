#ifndef _CONTROLLED_PLAYER_H
#define _CONTROLLED_PLAYER_H

#include "player.h"
#include "network/client.h"

class Client;

class ControlledPlayer final : Player {
  private:
    Client* client;

  public:
    ControlledPlayer(btRigidBody* body);
    void update(float mouseXDelta);
    glm::mat4 getTransform();
};

#endif
