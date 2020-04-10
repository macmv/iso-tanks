#include "shoot_event.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "src/proto/multiplayer.grpc.pb.h"
#include "network/proto_util.h"

ShootEvent::ShootEvent(glm::mat4 transform) {
 this->transform = transform;
}

ShootEvent::ShootEvent(PlayerShootEvent proto) {
 this->transform = ProtoUtil::to_glm(proto.transform());
}

void ShootEvent::toProto(PlayerShootEvent* proto) {
  proto->set_exists(true);
  ProtoUtil::to_proto(transform, proto->mutable_transform());
}
