#include "proto_util.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

glm::mat4 ProtoUtil::to_glm(Transform trans) {
  glm::mat4 transform = glm::mat4(1);
  transform = glm::translate(transform, glm::vec3(trans.position().x(), trans.position().y(), trans.position().z()));
  transform = transform * glm::toMat4(glm::quat(trans.rotation().w(), trans.rotation().x(), trans.rotation().y(), trans.rotation().z()));
  return transform;
}

