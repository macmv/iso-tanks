#include "world.h"
#include "opengl/camera.h"
#include "player/player.h"
#include "player/projectile/missile.h"
#include "network/proto_util.h"
#include "player/settings/controller.h"
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
  collision_shapes->insert({ "player", shape });

  cylinder = new btCylinderShape(btVector3(1, 1, 1));
  t.setIdentity();
  t.setOrigin(btVector3(0, 0, 0));
  collision_shapes->insert({ "missile", cylinder });

  btRigidBody* body = add_body(glm::mat4(1), "ground", 0);
  body->setFriction(.8);
  body->setRollingFriction(.8);

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

World::World(Terrain* terrain, bool needs_debug, SceneManager* scene_manager, ParticleManager* particle_manager) : World(terrain, needs_debug) {
  this->scene_manager = scene_manager;
  this->particle_manager = particle_manager;
}

void World::draw_debug() {
  debug_draw->start();
  dynamics_world->debugDrawWorld();
  debug_draw->end();
}

void World::clean() {
}

void World::create_this_player(Controller* controller, Camera* camera) {
  btRigidBody* body = add_body(glm::translate(glm::mat4(1), glm::vec3(0, -970, 0)), "player", 1);
  body->setFriction(.5);
  body->setSpinningFriction(.3);

  this_player = new ControlledPlayer(body, controller, scene_manager, camera);
}

uint World::add_player() {
  uint id = (uint) rand();
  add_player(id);
  return id;
}

void World::add_player(uint id) {
  btRigidBody* body = add_body(glm::mat4(1), "player", 1);
  body->setFriction(.5);
  body->setSpinningFriction(.3);

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

  // cout << "----------------------------------------------" << endl;
  // for (int j = dynamics_world->getNumCollisionObjects() - 1; j >= 0; j--) {
  //   btCollisionObject* obj = dynamics_world->getCollisionObjectArray()[j];
  //   btRigidBody* body = btRigidBody::upcast(obj);
  //   btTransform trans;
  //   if (body && body->getMotionState()) {
  //     body->getMotionState()->getWorldTransform(trans);
  //   } else {
  //     trans = obj->getWorldTransform();
  //   }
  //   printf("Object: %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
  // }
  // cout << "There are " << dynamics_world->getNumCollisionObjects() << " objects in the world" << endl;
  // cout << "----------------------------------------------" << endl;

  // makes sure no one touches the world while stepping the simulation
  world_mutex.lock();

  ulong update_time =
    std::chrono::system_clock::now().time_since_epoch() /
    std::chrono::milliseconds(1);
  dynamics_world->stepSimulation((double) (update_time - prev_update) / 1000, 10);
  prev_update = update_time;

  world_mutex.unlock();

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
      projectile->set_gravity(pos);
    }
    projectile->update();
  }
}

// client function
void World::add_projectile(ProjectileProto proto) {
  if (scene_manager == NULL) {
    cerr << "Cannot add_projectile without player_id on server!" << endl;
    cerr << "Force exiting server" << endl;
    exit(1);
  }

  btRigidBody* body = add_body(glm::mat4(1), "missile", .1f);

  glm::mat4 transform = ProtoUtil::to_glm(proto.transform());
  glm::vec3 vel = ProtoUtil::to_glm(proto.velocity());

  projectiles->insert({ proto.id(), new Missile(transform, vel, body, scene_manager, particle_manager) });
}

// server function
void World::add_projectile(uint player_id, ProjectileProto proto) {
  if (scene_manager != NULL) {
    cerr << "Cannot add_projectile with player_id on client!" << endl;
    cerr << "Force exiting client" << endl;
    exit(1);
  }

  btRigidBody* body = add_body(glm::mat4(1), "missile", .1f);

  glm::mat4 transform = ProtoUtil::to_glm(proto.transform());
  // rotate upward vector to face the corrrect direction
  glm::vec3 vel = glm::vec3(transform * glm::vec4(0, 0, 1, 0));
  // make the projectile spawn in front of the player, not inside
  transform[3] = transform[3] + glm::vec4(vel * 1.5f, 0);
  // gotta go fast
  vel = vel * 200.f;

  uint id = (uint) rand();
  projectiles->insert({ id, new Missile(transform, vel, body) });
}

bool World::has_projectile(uint id) {
  return projectiles->find(id) != projectiles->end();
}

btRigidBody* World::add_body(glm::mat4 trans, string shape_name, float mass) {
  btCollisionShape* shape = collision_shapes->at(shape_name);

  btTransform start_transform = btTransform(btMatrix3x3(trans[0][0], trans[1][0], trans[2][0],
                                                        trans[0][1], trans[1][1], trans[2][1],
                                                        trans[0][2], trans[1][2], trans[2][2]),
                                            btVector3(trans[3][0], trans[3][1], trans[3][2]));

  btVector3 local_inertia(0, 0, 0);
  shape->calculateLocalInertia(mass, local_inertia);

  btDefaultMotionState* motion_state = new btDefaultMotionState(start_transform);
  btRigidBody::btRigidBodyConstructionInfo info(mass, motion_state, shape, local_inertia);
  btRigidBody* body = new btRigidBody(info);

  // makes sure no one is editing the world while we add a body
  world_mutex.lock();
  dynamics_world->addRigidBody(body);
  world_mutex.unlock();

  return body;
}
