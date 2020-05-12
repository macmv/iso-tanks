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

ControlledPlayer::ControlledPlayer(rp3d::RigidBody* body, Controller* controller, SceneManager* scene_manager, Camera* camera) : Player(body, scene_manager) {
  this->controller = controller;
  for (ModelInstance* model : *scene->models) {
    if (model->model->name.compare("Turret") == 0) {
      turret_transform = model->transform;
    }
  }
}

void ControlledPlayer::update(float mouse_x_delta) {
  rp3d::Transform body_transform = body->getTransform();
  body_transform.getOpenGLMatrix(glm::value_ptr(transform));
  scene->transform = transform;

  float torque_amount = 0;
  glm::vec3 force = glm::vec3(0, 0, 0);
  glm::vec3 up = glm::normalize(glm::vec3(transform[3]) * -1.f);
  glm::vec3 forward = glm::vec3(transform * glm::vec4(0, 0, 1, 0));
  // glm::vec3 left = cross(up, forward);

  glm::vec3 vel = glm::vec3(body->getLinearVelocity().x, body->getLinearVelocity().y, body->getLinearVelocity().z);
  glm::vec3 ang_vel = glm::vec3(body->getAngularVelocity().x, body->getAngularVelocity().y, body->getAngularVelocity().z);
  float speed = .9f - glm::length(vel) / 10;
  if (speed < 0) {
    speed = 0;
  }
  float torque_speed = (0.1f - glm::length(ang_vel * up) / 10) * 6;
  if (torque_speed < 0) {
    torque_speed = 0;
  }

  if (controller->is_action_pressed("forward")) {
    force += forward * speed;
  }
  if (controller->is_action_pressed("left")) {
    torque_amount += torque_speed;
  }
  if (controller->is_action_pressed("backward")) {
    force += -forward * speed;
  }
  if (controller->is_action_pressed("right")) {
    torque_amount -= torque_speed;
  }

  body->setIsActive(true);
  body->applyForceToCenterOfMass(rp3d::Vector3(force.x, force.y, force.z));

  glm::vec3 torqueForce = up * torque_amount;
  body->applyTorque(rp3d::Vector3(torqueForce.x, torqueForce.y, torqueForce.z));

  float turret_delta = mouse_x_delta;
  turret_angle += turret_delta;

  for (ModelInstance* model : *scene->models) {
    if (model->model->name.compare("Turret") == 0) {
      model->transform = glm::rotate(glm::mat4(1), turret_angle, glm::vec3(0, 1, 0)) * turret_transform;
    }
  }
}

void ControlledPlayer::update_events(EventList* events) {
  if (controller->is_action_pressed("fire")) {
    events->shoot(transform * glm::rotate(glm::mat4(1), turret_angle, glm::vec3(0, 1, 0)));
  }
}

