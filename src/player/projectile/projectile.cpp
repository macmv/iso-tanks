#include "projectile.h"
#include "network/proto_util.h"
#include "src/proto/multiplayer.grpc.pb.h"
#include <glm/gtx/string_cast.hpp>

using namespace std;

Projectile::Projectile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body, SceneManager* scene_manager, string scene_name) : Projectile(transform, velocity, body) {
  scene = scene_manager->new_instance(scene_name);
  update();
}

Projectile::Projectile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body) {
  btTransform body_transform = btTransform(btMatrix3x3(transform[0][0], transform[1][0], transform[2][0],
                                                       transform[0][1], transform[1][1], transform[2][1],
                                                       transform[0][2], transform[1][2], transform[2][2]),
                                             btVector3(transform[3][0], transform[3][1], transform[3][2]));
  body->setWorldTransform(body_transform);
  body->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
  this->body = body;
  update();
}

void Projectile::update() {
  btTransform body_transform = body->getWorldTransform();
  body_transform.getOpenGLMatrix(glm::value_ptr(transform));

  if (scene != NULL) {
    scene->transform = transform;
  }

  btVector3 body_velocity = body->getLinearVelocity();
  velocity.x = body_velocity.x();
  velocity.y = body_velocity.y();
  velocity.z = body_velocity.z();
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

glm::vec3 Projectile::get_velocity() {
  return velocity;
}
