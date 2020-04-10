#include "world.h"
#include "opengl/camera.h"
#include "player/player.h"
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

World::World(Terrain* terrain, bool needsDebug) {
  // init

  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher             = new btCollisionDispatcher(collisionConfiguration);
  overlappingPairCache   = new btDbvtBroadphase();
  solver                 = new btSequentialImpulseConstraintSolver;

  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

  collisionShapes = new std::vector<btCollisionShape*>();

  btTriangleMesh* mesh = new btTriangleMesh();
  for (ulong i = 0; i < terrain->indices->size() / 3; i++) {
    glm::vec3 a = terrain->vertices->at(terrain->indices->at(i * 3 + 0));
    glm::vec3 b = terrain->vertices->at(terrain->indices->at(i * 3 + 1));
    glm::vec3 c = terrain->vertices->at(terrain->indices->at(i * 3 + 2));
    mesh->addTriangle(btVector3(a.x, a.y, a.z), btVector3(b.x, b.y, b.z), btVector3(c.x, c.y, c.z));
  }

  btCollisionShape* groundShape = new btBvhTriangleMeshShape(mesh, true, true);
  collisionShapes->push_back(groundShape);

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
  collisionShapes->push_back(shape);

  btTransform groundTransform;
  groundTransform.setIdentity();
  groundTransform.setOrigin(btVector3(0, 0, 0));

  float mass = 0.f;

  btVector3 localInertia(0, 0, 0);

  //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
  btRigidBody* body = new btRigidBody(rbInfo);
  body->setFriction(.8);
  body->setRollingFriction(.8);

  //add the body to the dynamics world
  dynamicsWorld->addRigidBody(body);

  players = new std::unordered_map<uint, Player*>();
  models = new std::vector<ModelInstance*>();


  if (needsDebug) {
    debugDraw = new DebugDraw();
    debugDraw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    dynamicsWorld->setDebugDrawer(debugDraw);
  }

  prev_update =
    std::chrono::system_clock::now().time_since_epoch() /
    std::chrono::milliseconds(1);

  thisPlayer = NULL;

  srand(time(0));
}

void World::drawDebug() {
  debugDraw->start();
  dynamicsWorld->debugDrawWorld();
  debugDraw->end();
}

void World::clean() {
}

void World::createThisPlayer(Camera* camera) {
  btCollisionShape* shape = collisionShapes->at(1);

  btTransform startTransform;
  startTransform.setIdentity();

  float mass = 1.f;
  btVector3 localInertia(0, 0, 0);
  shape->calculateLocalInertia(mass, localInertia);
  startTransform.setOrigin(btVector3(0, 840, 0));
  startTransform.getBasis().setEulerZYX(180, 0, 0);

  //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
  btRigidBody* body = new btRigidBody(rbInfo);
  body->setFriction(.5);
  body->setSpinningFriction(.3);

  dynamicsWorld->addRigidBody(body);

  thisPlayer = new ControlledPlayer(body, camera);
}

uint World::addPlayer() {
  uint id = (uint) rand();
  addPlayer(id);
  return id;
}

void World::addPlayer(uint id) {
  btCollisionShape* shape = collisionShapes->at(1);

  btTransform startTransform;
  startTransform.setIdentity();

  float mass = 1.f;
  btVector3 localInertia(0, 0, 0);
  shape->calculateLocalInertia(mass, localInertia);
  startTransform.setOrigin(btVector3(0, -900, 0));

  //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
  btRigidBody* body = new btRigidBody(rbInfo);
  body->setFriction(.5);
  body->setSpinningFriction(.3);

  dynamicsWorld->addRigidBody(body);

  Player* player = new Player(body);
  players->insert({id, player});
}

bool World::hasPlayer(uint id) {
  return players->find(id) != players->end();
}

ControlledPlayer* World::getPlayer() {
  return thisPlayer;
}

bool World::moveThisPlayer(glm::mat4 transform) {
  thisPlayer->setTransform(transform);
  return true;
}

bool World::movePlayer(uint id, glm::mat4 transform) {
  Player* p = players->at(id);
  p->setTransform(transform);
  return true;
}

World::~World() {
  for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
    btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
    btRigidBody* body = btRigidBody::upcast(obj);
    if (body && body->getMotionState()) {
      delete body->getMotionState();
    }
    dynamicsWorld->removeCollisionObject(obj);
    delete obj;
  }

  for (ulong i = 0; i < collisionShapes->size(); i++) {
    btCollisionShape* shape = collisionShapes->at(i);
    collisionShapes->at(i) = 0;
    delete shape;
  }

  delete dynamicsWorld;
  delete solver;
  delete overlappingPairCache;
  delete dispatcher;
  delete collisionConfiguration;

  collisionShapes->clear();
}

void World::updateControls(float mouseXDelta) {
  glm::vec3 pos = glm::vec3(thisPlayer->scene->transform[3]);
  pos = glm::normalize(pos) * 20.f;
  if (!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z)) {
    thisPlayer->setGravity(pos);
  }
  thisPlayer->update(mouseXDelta);
}

void World::update() {
  ulong update_time =
    std::chrono::system_clock::now().time_since_epoch() /
    std::chrono::milliseconds(1);
  dynamicsWorld->stepSimulation((double) (update_time - prev_update) / 1000, 10);
  prev_update = update_time;

  Player* player;
  for (std::pair<int, Player*> pair : *players) {
    player = pair.second;
    glm::vec3 pos = glm::vec3(player->scene->transform[3]);
    pos = glm::normalize(pos) * 20.f;
    if (!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z)) {
      player->setGravity(pos);
    }
    player->update();
  }

  // for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
  //   btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
  //   btRigidBody* body = btRigidBody::upcast(obj);
  //   btTransform trans;
  //   if (body && body->getMotionState()) {
  //     body->getMotionState()->getWorldTransform(trans);
  //   } else {
  //     trans = obj->getWorldTransform();
  //   }
  //   printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
  // }
}
