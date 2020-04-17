#include "world.h"
#include "opengl/camera.h"
#include "player/player.h"
#include "player/projectile/missile.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <cmath>
#include "debug.h"
#include <time.h>
#include <unordered_map>
#include <chrono>

using namespace std;

World::World(Terrain* terrain, bool needs_debug) {
  // init

  collision_configuration = new btDefaultCollisionConfiguration();
  dispatcher              = new btCollisionDispatcher(collision_configuration);
  overlapping_pair_cache  = new btDbvtBroadphase();
  solver                  = new btSequentialImpulseConstraintSolver();

  dynamics_world = new btDiscreteDynamicsWorld(dispatcher, overlapping_pair_cache, solver, collision_configuration);

  btTriangleMesh* mesh = new btTriangleMesh();
  for (ulong i = 0; i < terrain->indices->size() / 3; i++) {
    glm::vec3 a = terrain->vertices->at(terrain->indices->at(i * 3 + 0));
    glm::vec3 b = terrain->vertices->at(terrain->indices->at(i * 3 + 1));
    glm::vec3 c = terrain->vertices->at(terrain->indices->at(i * 3 + 2));
    mesh->addTriangle(btVector3(a.x, a.y, a.z), btVector3(b.x, b.y, b.z), btVector3(c.x, c.y, c.z));
  }

  btCollisionShape* ground_shape = new btBvhTriangleMeshShape(mesh, true, true);
  collision_shapes->insert({ "ground", ground_shape });

  btTransform t;

  //btCollisionShape* shape = new btSphereShape(btScalar(1.));
  btCollisionShape* cube = new btBoxShape(btVector3(1, .1, 1));
  btCollisionShape* cylinder = new btCylinderShapeX(btVector3(1.5, 1, 1));
  btCompoundShape* shape = new btCompoundShape();
  t.setIdentity();
  t.setOrigin(btVector3(0, -.9, 0));
  shape->addChildShape(t, cube);
  t.setIdentity();
  t.setOrigin(btVector3(0, 0, -1));
  shape->addChildShape(t, cylinder);
  t.setIdentity();
  t.setOrigin(btVector3(0, 0, 1));
  shape->addChildShape(t, cylinder);
  collision_shapes->insert( {"player", shape} );

  cylinder = new btCylinderShape(btVector3(1, 1, 1));
  t.setIdentity();
  t.setOrigin(btVector3(0, 0, 0));
  collision_shapes->insert( {"missile", cylinder} );

  btTransform ground_transform;
  ground_transform.setIdentity();
  ground_transform.setOrigin(btVector3(0, 0, 0));

  float mass = 0.f;

  btVector3 local_inertia(0, 0, 0);

  //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* motion_state = new btDefaultMotionState(ground_transform);
  btRigidBody::btRigidBodyConstructionInfo info(mass, motion_state, ground_shape, local_inertia);
  btRigidBody* body = new btRigidBody(info);
  body->setFriction(.8);
  body->setRollingFriction(.8);

  //add the body to the dynamics world
  dynamics_world->addRigidBody(body);

  if (needs_debug) {
    debug_draw = new DebugDraw();
    debug_draw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    dynamics_world->setDebugDrawer(debug_draw);
  }

  prev_update =
    std::chrono::system_clock::now().time_since_epoch() /
    std::chrono::milliseconds(1);

  this_player = NULL;

  srand(time(0));
}

World::World(Terrain* terrain, bool needs_debug, SceneManager* scene_manager) : World(terrain, needs_debug) {
  this->scene_manager = scene_manager;
}

void World::draw_debug() {
  debug_draw->start();
  dynamics_world->debugDrawWorld();
  debug_draw->end();
}

void World::clean() {
}

void World::create_this_player(Camera* camera) {
  btCollisionShape* shape = collision_shapes->at("player");

  btTransform start_transform;
  start_transform.setIdentity();
  start_transform.setOrigin(btVector3(0, -970, 0));
  // startTransform.setOrigin(btVector3(0, 840, 0));
  // startTransform.getBasis().setEulerZYX(M_PI, 0, 0);

  float mass = 1.f;
  btVector3 local_inertia(0, 0, 0);
  shape->calculateLocalInertia(mass, local_inertia);

  //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* motion_state = new btDefaultMotionState(start_transform);
  btRigidBody::btRigidBodyConstructionInfo info(mass, motion_state, shape, local_inertia);
  btRigidBody* body = new btRigidBody(info);
  body->setFriction(.5);
  body->setSpinningFriction(.3);

  dynamics_world->addRigidBody(body);

  this_player = new ControlledPlayer(body, scene_manager, camera);
}

uint World::add_player() {
  uint id = (uint) rand();
  add_player(id);
  return id;
}

void World::add_player(uint id) {
  btCollisionShape* shape = collision_shapes->at("player");

  btTransform start_transform;
  start_transform.setIdentity();

  float mass = 1.f;
  btVector3 local_inertia(0, 0, 0);
  shape->calculateLocalInertia(mass, local_inertia);

  //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* motion_state = new btDefaultMotionState(start_transform);
  btRigidBody::btRigidBodyConstructionInfo info(mass, motion_state, shape, local_inertia);
  btRigidBody* body = new btRigidBody(info);
  body->setFriction(.5);
  body->setSpinningFriction(.3);

  dynamics_world->addRigidBody(body);

  Player* player = new Player(body, scene_manager);
  players->insert({id, player});
}

bool World::has_player(uint id) {
  return players->find(id) != players->end();
}

ControlledPlayer* World::get_this_player() {
  return this_player;
}

bool World::move_this_player(glm::mat4 transform) {
  this_player->set_transform(transform);
  return true;
}

bool World::move_player(uint id, glm::mat4 transform) {
  Player* p = players->at(id);
  p->set_transform(transform);
  return true;
}

World::~World() {
  for (int i = dynamics_world->getNumCollisionObjects() - 1; i >= 0; i--) {
    btCollisionObject* obj = dynamics_world->getCollisionObjectArray()[i];
    btRigidBody* body = btRigidBody::upcast(obj);
    if (body && body->getMotionState()) {
      delete body->getMotionState();
    }
    dynamics_world->removeCollisionObject(obj);
    delete obj;
  }

  for (pair<string, btCollisionShape*> items : *collision_shapes) {
    btCollisionShape* shape = items.second;
    delete shape;
  }
  collision_shapes->clear();

  delete dynamics_world;
  delete solver;
  delete overlapping_pair_cache;
  delete dispatcher;
  delete collision_configuration;
}

void World::update_controls(float mouse_x_delta) {
  glm::vec3 pos = glm::vec3(this_player->get_transform()[3]);
  pos = glm::normalize(pos) * 20.f;
  if (!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z)) {
    this_player->set_gravity(pos);
  }
  this_player->update(mouse_x_delta);
}

void World::update() {
  ulong update_time =
    std::chrono::system_clock::now().time_since_epoch() /
    std::chrono::milliseconds(1);

  cout << "----------------------------------------------" << endl;
  for (int j = dynamics_world->getNumCollisionObjects() - 1; j >= 0; j--) {
    btCollisionObject* obj = dynamics_world->getCollisionObjectArray()[j];
    btRigidBody* body = btRigidBody::upcast(obj);
    btTransform trans;
    if (body && body->getMotionState()) {
      body->getMotionState()->getWorldTransform(trans);
    } else {
      trans = obj->getWorldTransform();
    }
    printf("Object: %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
  }
  cout << "There are " << dynamics_world->getNumCollisionObjects() << " objects in the world" << endl;
  cout << "----------------------------------------------" << endl;

  dynamics_world->stepSimulation((double) (update_time - prev_update) / 1000, 10);
  prev_update = update_time;

  Player* player;
  for (pair<int, Player*> item : *players) {
    player = item.second;
    glm::vec3 pos = glm::vec3(player->get_transform()[3]);
    pos = glm::normalize(pos) * 20.f;
    if (!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z)) {
      player->set_gravity(pos);
    }
    player->update();
  }

  Projectile* projectile;
  for (pair<int, Projectile*> item : *projectiles) {
    projectile = item.second;
    glm::vec3 pos = glm::vec3(projectile->get_transform()[3]);
    pos = glm::normalize(pos) * 20.f;
    if (!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z)) {
      // projectile->set_gravity(pos);
    }
    projectile->update();
  }
}

void World::add_projectile(ProjectileProto proto) {
  btCollisionShape* shape = collision_shapes->at("missile");

  btTransform start_transform;
  start_transform.setIdentity();

  float mass = 1.f;
  btVector3 local_inertia(0, 0, 0);
  shape->calculateLocalInertia(mass, local_inertia);

  btDefaultMotionState* motion_state = new btDefaultMotionState(start_transform);
  btRigidBody::btRigidBodyConstructionInfo info(mass, motion_state, shape, local_inertia);
  btRigidBody* body = new btRigidBody(info);
  body->setFriction(0);
  body->setSpinningFriction(0);

  dynamics_world->addRigidBody(body);

  if (scene_manager == NULL) {
    // This is only run on the server, so we create the id
    uint id = (uint) rand();
    projectiles->insert({ id, new Missile(proto, body) });
  } else {
    projectiles->insert({ proto.id(), new Missile(proto, body, scene_manager) });
  }
}

bool World::has_projectile(uint id) {
  return projectiles->find(id) != projectiles->end();
}
