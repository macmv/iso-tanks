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
  loadScene("assets/player.glb", scene);
  turretAngle = 3;
}

void Player::update() {
  btTransform transform;
  body->getMotionState()->getWorldTransform(transform);
  transform.getOpenGLMatrix(glm::value_ptr(scene->transform));
}

glm::mat4 Player::getTransform() {
  return scene->transform;
}

void Player::setTransform(glm::mat4 trans) {
  btTransform bodyTransform = btTransform(btMatrix3x3(trans[0][0], trans[1][0], trans[2][0],
                                                      trans[0][1], trans[1][1], trans[2][1],
                                                      trans[0][2], trans[1][2], trans[2][2]),
                                          btVector3(trans[3][0], trans[3][1], trans[3][2]));
  body->activate();
  body->setWorldTransform(bodyTransform);
}

void Player::setGravity(glm::vec3 gravity) {
  body->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}
