#ifndef _CONTROLLED_PLAYER_H
#define _CONTROLLED_PLAYER_H

#include "player.h"

class ControlledPlayer final : public Player {

  public:
    ControlledPlayer(btRigidBody* body);
    void update(float mouseXDelta);
};

#endif
