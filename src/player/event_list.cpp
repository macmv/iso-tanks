#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "event_list.h"
#include "event/shoot_event.h"
#include "src/proto/multiplayer.grpc.pb.h"

EventList::EventList() {
  shootEvent = NULL;
}

void EventList::toProto(PlayerEvents* proto) {

}

void EventList::shoot(glm::quat direction) {
  shootEvent = new ShootEvent(direction);
}

