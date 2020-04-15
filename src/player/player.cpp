#include "player.h"
#include "opengl/loader.h"
#include "models/model_instance.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

Player::Player(btRigidBody* body) {
  this->body = body;
  scene = new Scene();
  load_scene("assets/player.glb", scene);
  turret_angle = 0;
  health = 100;
}

void Player::update() {
  btTransform transform;
  body->getMotionState()->getWorldTransform(transform);
  transform.getOpenGLMatrix(glm::value_ptr(scene->transform));
}

glm::mat4 Player::get_transform() {
  return scene->transform;
}

void Player::set_transform(glm::mat4 trans) {
  btTransform body_transform = btTransform(btMatrix3x3(trans[0][0], trans[1][0], trans[2][0],
                                                      trans[0][1], trans[1][1], trans[2][1],
                                                      trans[0][2], trans[1][2], trans[2][2]),
                                           btVector3(trans[3][0], trans[3][1], trans[3][2]));
  body->activate();
  body->setWorldTransform(body_transform);
}

void Player::set_gravity(glm::vec3 gravity) {
  body->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}
