#include "projectile.h"
#include "network/proto_util.h"
#include "src/proto/multiplayer.grpc.pb.h"

using namespace std;

Projectile::Projectile(ProjectileProto proto, btRigidBody* body, SceneManager* scene_manager, string scene_name) : Projectile(proto, body) {
  scene = scene_manager->new_instance(scene_name);
  delete transform;
  transform = &scene->transform;
}

Projectile::Projectile(ProjectileProto proto, btRigidBody* body) {
  transform = new glm::mat4(1);
  glm::mat4 trans = ProtoUtil::to_glm(proto.transform());
  btTransform body_transform = btTransform(btMatrix3x3(trans[0][0], trans[1][0], trans[2][0],
                                                       trans[0][1], trans[1][1], trans[2][1],
                                                       trans[0][2], trans[1][2], trans[2][2]),
                                             btVector3(trans[3][0], trans[3][1], trans[3][2]));
  body->getMotionState()->setWorldTransform(body_transform);
}

float Projectile::get_speed() {
  return speed;
}

Scene* Projectile::get_scene() {
  return scene;
}

glm::mat4 Projectile::get_transform() {
  return *transform;
}
