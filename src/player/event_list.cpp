#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "event_list.h"
#include "event/shoot_event.h"
#include "src/proto/multiplayer.grpc.pb.h"
#include <iostream>

using namespace std;

EventList::EventList() {
  shoot_event = NULL;
}

void EventList::to_proto(PlayerEvents* proto) {
  if (shoot_event != NULL) {
    shoot_event->to_proto(proto->mutable_shoot());
    delete shoot_event;
    shoot_event = NULL;
  }
}

void EventList::shoot(glm::mat4 transform) {
  delete shoot_event;
  shoot_event = new ShootEvent(transform);
}

