#include "projectile.h"
#include "network/proto_util.h"
#include "src/proto/multiplayer.grpc.pb.h"
#include <glm/gtx/string_cast.hpp>

using namespace std;

Projectile::Projectile(glm::mat4 transform,
    glm::vec3 velocity,
    rp3d::RigidBody* body,
    SceneManager* scene_manager,
    string scene_name) : Projectile(transform,
      velocity,
      body) {
  scene = scene_manager->new_instance(scene_name);
  update();
}

Projectile::Projectile(glm::mat4 transform, glm::vec3 velocity, rp3d::RigidBody* body) {
  rp3d::Transform body_transform = rp3d::Transform(rp3d::Vector3(transform[3][0], transform[3][1], transform[3][2]),
                                                   rp3d::Matrix3x3(transform[0][1], transform[1][1], transform[2][1],
                                                                   transform[0][2], transform[1][2], transform[2][2],
                                                                   transform[0][3], transform[1][3], transform[2][3]));
  //body->setTransform(body_transform);
  //body->setLinearVelocity(rp3d::Vector3(velocity.x, velocity.y, velocity.z));
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
