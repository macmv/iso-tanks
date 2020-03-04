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

  float torqueAmount = 0;
  glm::vec3 force = glm::vec3(0, 0, 0);
  glm::vec3 up = glm::normalize(glm::vec3(scene->transform[3]) * -1.f);
  glm::vec3 forward = glm::vec3(scene->transform * glm::vec4(0, 0, 1, 0));
  glm::vec3 left = cross(up, forward);

  glm::vec3 vel = glm::vec3(body->getLinearVelocity().x(), body->getLinearVelocity().y(), body->getLinearVelocity().z());
  glm::vec3 angVel = glm::vec3(body->getAngularVelocity().x(), body->getAngularVelocity().y(), body->getAngularVelocity().z());
  float speed = .8f - glm::length(vel) / 10;
  float torqueSpeed = 0.1f - glm::length(angVel * up) / 10;

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
  body->applyTorqueImpulse(btVector3(torqueForce.x, torqueForce.y, torqueForce.z));

  for (ModelInstance* model : *scene->models) {
    if (model->model->name.compare("Turret") == 0) {
      model->transform = glm::rotate(glm::mat4(1), .1f, glm::vec3(0, 1, 0)) * model->transform;
    }
  }
}

glm::mat4 Player::getTransform() {
  return scene->transform;
}
