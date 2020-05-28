#include "projectile.h"
#include "network/proto_util.h"
#include "src/proto/multiplayer.grpc.pb.h"
#include <glm/gtx/string_cast.hpp>

using namespace std;

Projectile::Projectile(rp3d::RigidBody* body,
    SceneManager* scene_manager,
    string scene_name) : Projectile(body) {
  scene = scene_manager->new_instance(scene_name);
  update();
}

Projectile::Projectile(rp3d::RigidBody* body) {
  this->body = body;
  update();
}

void Projectile::update() {
  rp3d::Transform body_transform = body->getTransform();
  body_transform.getOpenGLMatrix(glm::value_ptr(transform));

  if (scene != NULL) {
    scene->transform = transform;
  }

  rp3d::Vector3 body_velocity = body->getLinearVelocity();
  velocity.x = body_velocity.x;
  velocity.y = body_velocity.y;
  velocity.z = body_velocity.z;
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

void Projectile::set_gravity(glm::vec3 gravity) {
  // body->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}
