#include "player.h"
#include "../opengl/loader.h"
#include "../models/model_instance.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <bullet/btBulletDynamicsCommon.h>

Player::Player(btRigidBody* body) {
  this->body = body;
  Model* model = new Model();
  loadModel("assets/player.obj", model);
  instance = new ModelInstance(model);
}

void Player::update() {
  btTransform transform;
  body->getMotionState()->getWorldTransform(transform);
  transform.getOpenGLMatrix(glm::value_ptr(instance->transform));
}
