#ifndef _SHOOT_EVENT_H
#define _SHOOT_EVENT_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "src/proto/multiplayer.grpc.pb.h"

class ShootEvent {
  private:
    glm::quat direction;

  public:
    ShootEvent(glm::quat direction);
    ShootEvent(PlayerShootEvent proto);
    void toProto(PlayerShootEvent* proto);
};

#endif
