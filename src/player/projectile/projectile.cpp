#include "projectile.h"
#include "network/proto_util.h"
#include "src/proto/multiplayer.grpc.pb.h"
#include <glm/gtx/string_cast.hpp>

using namespace std;

Projectile::Projectile(glm::mat4 transform,
    glm::vec3 velocity,
    btRigidBody* body,
    SceneManager* scene_manager,
    ParticleCloud* cloud,
    string scene_name) : Projectile(transform,
      velocity,
      body) {
  scene = scene_manager->new_instance(scene_name);
  this->cloud = cloud;
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
  cloud = NULL;
  update();
}

void Projectile::update() {
  btTransform body_transform = body->getWorldTransform();
  body_transform.getOpenGLMatrix(glm::value_ptr(transform));

  if (scene != NULL) {
    scene->transform = transform;
    cloud->set_position(glm::vec3(get_transform()[3]));
    cloud->update();
  }

  btVector3 body_velocity = body->getLinearVelocity();
  velocity.x = body_velocity.x();
  velocity.y = body_velocity.y();
  velocity.z = body_velocity.z();
}

void Projectile::render(Render* render) {
  render->render(cloud);
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
  body->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}
