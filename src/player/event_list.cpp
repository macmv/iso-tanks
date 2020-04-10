#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "event_list.h"
#include "event/shoot_event.h"
#include "src/proto/multiplayer.grpc.pb.h"
#include <iostream>

using namespace std;

EventList::EventList() {
  shootEvent = NULL;
}

void EventList::toProto(PlayerEvents* proto) {
  if (shootEvent != NULL) {
    cout << "Sending shoot event!" << endl;
    shootEvent->toProto(proto->mutable_shoot());
  }
}

void EventList::shoot(glm::quat direction) {
  shootEvent = new ShootEvent(direction);
}

