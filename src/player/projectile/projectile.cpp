#include "projectile.h"
#include "network/proto_util.h"
#include "src/proto/multiplayer.grpc.pb.h"

Projectile::Projectile(ShootEvent event, btRigidBody* body, SceneManager* scene_manager, string scene_name) : Projectile(event, body) {
  scene = scene_manager->new_instance(scene_name);
}

Projectile::Projectile(ShootEvent event, btRigidBody* body) {
  btTransform transform = btTransform(btMatrix3x3(event.transform[0][0], event.transform[1][0], event.transform[2][0],
                                                  event.transform[0][1], event.transform[1][1], event.transform[2][1],
                                                  event.transform[0][2], event.transform[1][2], event.transform[2][2]),
                                      btVector3(event.transform[3][0], event.transform[3][1], event.transform[3][2]));
  body->getMotionState()->setWorldTransform(transform);
}

Scene* Projectile::get_scene() {
  return scene;
}
