#include "proto_util.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include "player/player.h"
#include "player/projectile/projectile.h"

using namespace std;

glm::mat4 ProtoUtil::to_glm(Transform trans) {
  glm::mat4 transform = glm::mat4(1);
  transform = glm::translate(transform, glm::vec3(trans.position().x(), trans.position().y(), trans.position().z()));
  transform = transform * glm::toMat4(glm::quat(trans.rotation().w(), trans.rotation().x(), trans.rotation().y(), trans.rotation().z()));
  return transform;
}

void ProtoUtil::to_proto(glm::mat4 transform, Transform* proto) {
  glm::vec3 position = glm::vec3(transform[3]);
  glm::quat rotation = glm::quat_cast(transform);

  proto->mutable_position()->set_x(position.x);
  proto->mutable_position()->set_y(position.y);
  proto->mutable_position()->set_z(position.z);
  proto->mutable_rotation()->set_x(rotation.x);
  proto->mutable_rotation()->set_y(rotation.y);
  proto->mutable_rotation()->set_z(rotation.z);
  proto->mutable_rotation()->set_w(rotation.w);
}

void ProtoUtil::to_proto(PlayerProto* proto, uint id, Player* player) {
  to_proto(player->get_transform(), proto->mutable_transform());
  proto->set_id(id);
}

void ProtoUtil::to_proto(ProjectileProto* proto, uint id, Projectile* projectile) {
  to_proto(projectile->get_transform(), proto->mutable_transform());
  proto->set_id(id);
  // set type here as well!
}
