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
      turret_start_transform = model->transform;
      turret_model = model;
      break;
    }
  }
  // body->setAngularDamping(100);
}

void ControlledPlayer::update() {
  rp3d::Transform body_transform = body->getTransform();
  body_transform.getOpenGLMatrix(glm::value_ptr(transform));
  scene->transform = transform;

  glm::vec3 up = glm::normalize(glm::vec3(transform[3]) * -1.f);
  glm::vec3 forward(transform * glm::vec4(0, 0, 1, 0));
  // glm::vec3 left = cross(up, forward);

  glm::vec3 vel = glm::vec3(body->getLinearVelocity().x, body->getLinearVelocity().y, body->getLinearVelocity().z);
  glm::vec3 ang_vel = glm::vec3(body->getAngularVelocity().x, body->getAngularVelocity().y, body->getAngularVelocity().z);
  float amount = 100;
  float torque_amount = 10;

  glm::vec3 force(0);
  float torque_force = 0;

  if (controller->is_action_pressed("forward")) {
    force += forward * amount;
  }
  if (controller->is_action_pressed("left")) {
    torque_force += torque_amount;
  }
  if (controller->is_action_pressed("backward")) {
    force += -forward * amount;
  }
  if (controller->is_action_pressed("right")) {
    torque_force -= torque_amount;
  }

  body->setIsActive(true);
  body->applyForceToCenterOfMass(rp3d::Vector3(force.x, force.y, force.z));

  glm::vec3 torque_vec = up * torque_force;
  body->applyTorque(rp3d::Vector3(torque_vec.x, torque_vec.y, torque_vec.z));

  float turret_delta = 0; // mouse x delta
  turret_angle += turret_delta;

  turret_model->transform = glm::rotate(glm::mat4(1), turret_angle, glm::vec3(0, 1, 0)) * turret_start_transform;
}

void ControlledPlayer::update_events(EventList* events) {
  if (controller->is_action_pressed("fire")) {
    events->shoot(transform * glm::rotate(glm::mat4(1), turret_angle, glm::vec3(0, 1, 0)));
  }
}

