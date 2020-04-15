#include "controlled_player.h"
#include "opengl/camera.h"
#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

using namespace std;

ControlledPlayer::ControlledPlayer(btRigidBody* body, Camera* camera) : Player(body) {
  for (ModelInstance* model : *scene->models) {
    if (model->model->name.compare("Turret") == 0) {
      turret_transform = model->transform;
    }
  }
  camera->set_player_transform(&scene->transform);
}

void ControlledPlayer::update(float mouse_x_delta) {
  btTransform transform;
  body->getMotionState()->getWorldTransform(transform);
  transform.getOpenGLMatrix(glm::value_ptr(scene->transform));

  float torque_amount = 0;
  glm::vec3 force = glm::vec3(0, 0, 0);
  glm::vec3 up = glm::normalize(glm::vec3(scene->transform[3]) * -1.f);
  glm::vec3 forward = glm::vec3(scene->transform * glm::vec4(0, 0, 1, 0));
  // glm::vec3 left = cross(up, forward);

  glm::vec3 vel = glm::vec3(body->getLinearVelocity().x(), body->getLinearVelocity().y(), body->getLinearVelocity().z());
  glm::vec3 ang_vel = glm::vec3(body->getAngularVelocity().x(), body->getAngularVelocity().y(), body->getAngularVelocity().z());
  float speed = .9f - glm::length(vel) / 10;
  if (speed < 0) {
    speed = 0;
  }
  float torque_speed = (0.1f - glm::length(ang_vel * up) / 10) * 6;
  if (torque_speed < 0) {
    torque_speed = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    force += forward * speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    torque_amount += torque_speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    force += -forward * speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    torque_amount -= torque_speed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    force += glm::vec3(0, speed, 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
    force += glm::vec3(0, -speed, 0);
  }

  body->activate();
  body->applyCentralImpulse(btVector3(force.x, force.y, force.z));

  glm::vec3 torqueForce = up * torque_amount;
  body->applyTorqueImpulse(btVector3(torqueForce.x, torqueForce.y, torqueForce.z));

  float turret_delta = mouse_x_delta;
  turret_angle += turret_delta;

  for (ModelInstance* model : *scene->models) {
    if (model->model->name.compare("Turret") == 0) {
      model->transform = glm::rotate(glm::mat4(1), turret_angle, glm::vec3(0, 1, 0)) * turret_transform;
    }
  }
}

