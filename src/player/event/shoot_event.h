#ifndef _SHOOT_EVENT_H
#define _SHOOT_EVENT_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "src/proto/multiplayer.grpc.pb.h"

class ShootEvent {
  private:
    glm::mat4 transform;

  public:
    ShootEvent(glm::mat4 transform);
    ShootEvent(PlayerShootEvent proto);
    void to_proto(PlayerShootEvent* proto);
};

#endif
