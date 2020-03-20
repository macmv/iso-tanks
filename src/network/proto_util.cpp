#include "proto_util.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "player/player.h"

glm::mat4 ProtoUtil::to_glm(Transform trans) {
  glm::mat4 transform = glm::mat4(1);
  transform = glm::translate(transform, glm::vec3(trans.position().x(), trans.position().y(), trans.position().z()));
  transform = transform * glm::toMat4(glm::quat(trans.rotation().w(), trans.rotation().x(), trans.rotation().y(), trans.rotation().z()));
  return transform;
}

void ProtoUtil::to_proto(PlayerProto* proto, uint id, Player* player) {
  glm::vec3 position = glm::vec3(player->getTransform()[3]);
  glm::quat rotation = glm::quat_cast(player->getTransform());

  proto->mutable_transform()->mutable_position()->set_x(position.x);
  proto->mutable_transform()->mutable_position()->set_y(position.y);
  proto->mutable_transform()->mutable_position()->set_z(position.z);
  proto->mutable_transform()->mutable_rotation()->set_x(rotation.x);
  proto->mutable_transform()->mutable_rotation()->set_y(rotation.y);
  proto->mutable_transform()->mutable_rotation()->set_z(rotation.z);
  proto->mutable_transform()->mutable_rotation()->set_w(rotation.w);
  proto->set_id(id);
}

