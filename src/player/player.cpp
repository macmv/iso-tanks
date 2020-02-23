#include "player.h"
#include "../opengl/loader.h"
#include "../models/model_instance.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

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

  float speed = .5f;

  glm::vec3 force = glm::vec3(0, 0, 0);
  glm::vec3 up = glm::normalize(glm::vec3(instance->transform[3]) * -1.f);
  glm::vec3 forward = glm::vec3(instance->transform * glm::vec4(0, 0, 1, 0));
  glm::vec3 left = cross(up, forward);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    force += forward * speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    force += left * speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    force += -forward * speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    force += -left * speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    force += glm::vec3(0, speed, 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
    force += glm::vec3(0, -speed, 0);
  }

  body->activate();
  body->applyCentralImpulse(btVector3(force.x, force.y, force.z));
}
