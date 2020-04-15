#ifndef _EVENT_LIST_H
#define _EVENT_LIST_H

#include <glm/glm.hpp>
#include "event/shoot_event.h"
#include "src/proto/multiplayer.grpc.pb.h"
#include "controlled_player.h"

class EventList {
  private:
    ShootEvent* shoot_event;

  public:
    EventList();
    void to_proto(PlayerEvents* proto);
    void shoot(ControlledPlayer* player);
};

#endif
