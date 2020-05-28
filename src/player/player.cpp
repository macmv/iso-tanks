#include "player.h"
#include "opengl/loader.h"
#include "models/scene_manager.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

Player::Player(rp3d::RigidBody* body, SceneManager* scene_manager) {
  this->body = body;
  if (scene_manager != NULL) {
    scene = scene_manager->new_instance("assets/player.glb");
    transform = scene->transform;
  } else {
    transform = glm::mat4(1);
  }
  turret_angle = 0;
  health = 100;
}

void Player::update() {
  rp3d::Transform body_transform = body->getTransform();
  body_transform.getOpenGLMatrix(glm::value_ptr(transform));
}

glm::mat4 Player::get_transform() {
  return transform;
}

void Player::set_transform(glm::mat4 trans) {
  rp3d::Transform body_transform = rp3d::Transform(rp3d::Vector3(trans[3][0], trans[3][1], trans[3][2]),
                                                   rp3d::Matrix3x3(trans[0][0], trans[0][1], trans[0][2],
                                                                   trans[1][0], trans[1][1], trans[1][2],
                                                                   trans[2][0], trans[2][1], trans[2][2]));

  rp3d::Quaternion q = body_transform.getOrientation();
  q.normalize();
  body_transform.setOrientation(q);

  body->setIsActive(true);
  body->setTransform(body_transform);
}

void Player::set_gravity(glm::vec3 gravity) {
  // body->setGravity(rp3d::Vector3(gravity.x, gravity.y, gravity.z));
  body->enableGravity(true);
}
