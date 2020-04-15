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
    cout << "Sending shoot event!" << endl;
    shoot_event->to_proto(proto->mutable_shoot());
    delete shoot_event;
    shoot_event = NULL;
  }
}

void EventList::shoot(ControlledPlayer* player) {
  delete shoot_event;
  shoot_event = new ShootEvent(player->get_transform());
}

