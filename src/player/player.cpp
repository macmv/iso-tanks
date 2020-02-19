#include "player.h"
#include "../opengl/loader.h"
#include "../models/model_instance.h"
#include <bullet/btBulletDynamicsCommon.h>

Player::Player(btRigidBody* body) {
  this->body = body;
  Model* model = new Model();
  loadModel("assets/player.obj", model);
  instance = new ModelInstance(model);
}
