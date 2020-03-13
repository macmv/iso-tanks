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

glm::mat4 Player::getTransform() {
  return scene->transform;
}

void Player::setGravity(glm::vec3 gravity) {
  body->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}
