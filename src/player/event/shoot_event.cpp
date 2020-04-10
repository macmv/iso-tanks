#include "shoot_event.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "src/proto/multiplayer.grpc.pb.h"

ShootEvent::ShootEvent(glm::quat direction) {
 this->direction = direction;
}

void ShootEvent::toProto(PlayerShootEvent* proto) {
  proto->set_exists(true);
  proto->set_dirx(direction.x);
  proto->set_diry(direction.y);
  proto->set_dirz(direction.z);
  proto->set_dirw(direction.w);
}
