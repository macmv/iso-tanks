#include "shoot_event.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "src/proto/multiplayer.grpc.pb.h"
#include "network/proto_util.h"

ShootEvent::ShootEvent(ControlledPlayer* player) {
  transform = player->get_transform() * glm::rotate(glm::mat4(1), player->turret_angle, glm::vec3(0, 1, 0));
}

ShootEvent::ShootEvent(PlayerShootEvent proto) {
  this->transform = ProtoUtil::to_glm(proto.projectile().transform());
}

void ShootEvent::to_proto(PlayerShootEvent* proto) {
  proto->set_exists(true);
  ProtoUtil::to_proto(transform, proto->mutable_projectile()->mutable_transform());
}
