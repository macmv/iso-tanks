#include "world.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

World::World(Terrain* terrain) {
  // init

  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher             = new btCollisionDispatcher(collisionConfiguration);
  overlappingPairCache   = new btDbvtBroadphase();
  solver                 = new btSequentialImpulseConstraintSolver;

  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

  dynamicsWorld->setGravity(btVector3(0, -10, 0));

  collisionShapes = new btAlignedObjectArray<btCollisionShape*>();

  btTriangleMesh* mesh = new btTriangleMesh();
  for (int i = 0; i < terrain->indices->size() / 3; i++) {
    glm::vec3 a = terrain->vertices->at(terrain->indices->at(i * 3 + 0));
    glm::vec3 b = terrain->vertices->at(terrain->indices->at(i * 3 + 1));
    glm::vec3 c = terrain->vertices->at(terrain->indices->at(i * 3 + 2));
    mesh->addTriangle(btVector3(a.x, a.y, a.z), btVector3(b.x, b.y, b.z), btVector3(c.x, c.y, c.z));
  }
  btCollisionShape* groundShape = new btBvhTriangleMeshShape(mesh, true, true);
  collisionShapes->push_back(groundShape);

  btCollisionShape* sphereShape = new btSphereShape(btScalar(1.));
  //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
  collisionShapes->push_back(sphereShape);


  btTransform groundTransform;
  groundTransform.setIdentity();
  groundTransform.setOrigin(btVector3(0, 0, 0));

  float mass = 0.f;

  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0, 0, 0);
  if (isDynamic)
    groundShape->calculateLocalInertia(mass, localInertia);

  //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
  btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
  btRigidBody* body = new btRigidBody(rbInfo);

  //add the body to the dynamics world
  dynamicsWorld->addRigidBody(body);


  btTransform startTransform;
  startTransform.setIdentity();

  mass = 1.f;

  sphereShape->calculateLocalInertia(mass, localInertia);

  startTransform.setOrigin(btVector3(2, 10, 0));

  //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
  myMotionState = new btDefaultMotionState(startTransform);
  rbInfo = btRigidBody::btRigidBodyConstructionInfo(mass, myMotionState, sphereShape, localInertia);
  body = new btRigidBody(rbInfo);

  dynamicsWorld->addRigidBody(body);
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

  for (int i = 0; i < collisionShapes->size(); i++) {
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

void World::update() {
  dynamicsWorld->stepSimulation(1.f / 60.f, 10);

  for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
    btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
    btRigidBody* body = btRigidBody::upcast(obj);
    btTransform trans;
    if (body && body->getMotionState()) {
      body->getMotionState()->getWorldTransform(trans);
    } else {
      trans = obj->getWorldTransform();
    }
    printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
  }
}
