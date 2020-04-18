#ifndef _SHOOT_EVENT_H
#define _SHOOT_EVENT_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "player/controlled_player.h"
#include "src/proto/multiplayer.grpc.pb.h"

class ShootEvent {
  public:
    glm::mat4 transform;

  public:
    ShootEvent(ControlledPlayer* player);
    ShootEvent(PlayerShootEvent proto);
    void to_proto(PlayerShootEvent* proto);
};

#endif
