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
  scene = new Scene();
  loadScene("assets/player.glb", scene);
}

void Player::update() {
  btTransform transform;
  body->getMotionState()->getWorldTransform(transform);
  transform.getOpenGLMatrix(glm::value_ptr(scene->transform));

  float speed = .20f;
  float torqueSpeed = 5;

  float torqueAmount = 0;
  glm::vec3 force = glm::vec3(0, 0, 0);
  glm::vec3 up = glm::normalize(glm::vec3(scene->transform[3]) * -1.f);
  glm::vec3 forward = glm::vec3(scene->transform * glm::vec4(0, 0, 1, 0));
  glm::vec3 left = cross(up, forward);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    force += forward * speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    torqueAmount += torqueSpeed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    force += -forward * speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    torqueAmount -= torqueSpeed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    force += glm::vec3(0, speed, 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
    force += glm::vec3(0, -speed, 0);
  }

  body->activate();
  body->applyCentralImpulse(btVector3(force.x, force.y, force.z));

  glm::vec3 torqueForce = up * torqueAmount;
  body->applyTorque(btVector3(torqueForce.x, torqueForce.y, torqueForce.z));
}

glm::mat4 Player::getTransform() {
  return scene->transform;
}
