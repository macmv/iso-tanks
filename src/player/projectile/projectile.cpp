#include "projectile.h"
#include "network/proto_util.h"
#include "src/proto/multiplayer.grpc.pb.h"
#include <glm/gtx/string_cast.hpp>

using namespace std;

Projectile::Projectile(ProjectileProto proto, btRigidBody* body, SceneManager* scene_manager, string scene_name) : Projectile(proto, body) {
  scene = scene_manager->new_instance(scene_name);
}

Projectile::Projectile(ProjectileProto proto, btRigidBody* body) {
  transform = ProtoUtil::to_glm(proto.transform());
  btTransform body_transform = btTransform(btMatrix3x3(transform[0][0], transform[1][0], transform[2][0],
                                                       transform[0][1], transform[1][1], transform[2][1],
                                                       transform[0][2], transform[1][2], transform[2][2]),
                                             btVector3(transform[3][0], transform[3][1], transform[3][2]));
  body->setWorldTransform(body_transform);
  this->body = body;
}

void Projectile::update() {
  btTransform body_transform;
  body->getMotionState()->getWorldTransform(body_transform);
  body_transform.getOpenGLMatrix(glm::value_ptr(transform));
  if (scene != NULL) {
    scene->transform = transform;
  }
}

float Projectile::get_speed() {
  return speed;
}

Scene* Projectile::get_scene() {
  return scene;
}

glm::mat4 Projectile::get_transform() {
  return transform;
}
