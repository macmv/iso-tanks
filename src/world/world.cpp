#include "world.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

World::World(Terrain* terrain) {
  // init

  btDefaultCollisionConfiguration*     collisionConfiguration = new btDefaultCollisionConfiguration();
  btCollisionDispatcher*               dispatcher             = new btCollisionDispatcher(collisionConfiguration);
  btBroadphaseInterface*               overlappingPairCache   = new btDbvtBroadphase();
  btSequentialImpulseConstraintSolver* solver                 = new btSequentialImpulseConstraintSolver;

  btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

  dynamicsWorld->setGravity(btVector3(0, -10, 0));

  // init

  btAlignedObjectArray<btCollisionShape*> collisionShapes;

  cout << "size:" << endl;
  cout << terrain->indices->size() << endl;

  btTriangleMesh* mesh = new btTriangleMesh();

  for (int i = 0; i < terrain->indices->size() / 3; i++) {

  }

  mesh->addTriangle(btVector3(-10, 0, -10), btVector3(10, 0, -10), btVector3(0, 0, 10));

  btCollisionShape* groundShape = new btBvhTriangleMeshShape(mesh, true, true);
  collisionShapes.push_back(groundShape);

  btCollisionShape* sphereShape = new btSphereShape(btScalar(1.));
  //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
  collisionShapes.push_back(sphereShape);


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

  /// Do some simulation

  ///-----stepsimulation_start-----
  for (int i = 0; i < 150; i++) {
    dynamicsWorld->stepSimulation(1.f / 60.f, 10);

    //print positions of all objects
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

  ///-----stepsimulation_end-----

  //cleanup in the reverse order of creation/initialization

  ///-----cleanup_start-----

  //remove the rigidbodies from the dynamics world and delete them
  for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
    btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
    btRigidBody* body = btRigidBody::upcast(obj);
    if (body && body->getMotionState()) {
      delete body->getMotionState();
    }
    dynamicsWorld->removeCollisionObject(obj);
    delete obj;
  }

  //delete collision shapes
  for (int i = 0; i < collisionShapes.size(); i++) {
    btCollisionShape* shape = collisionShapes[i];
    collisionShapes[i] = 0;
    delete shape;
  }

  delete dynamicsWorld;

  delete solver;

  delete overlappingPairCache;

  delete dispatcher;

  delete collisionConfiguration;

  collisionShapes.clear();
}
