#ifndef _WORLD_H
#define _WORLD_H

#include "terrain/terrain.h"
#include <bullet/btBulletDynamicsCommon.h>

class World {
  private:
    btDefaultCollisionConfiguration*         collisionConfiguration;
    btCollisionDispatcher*                   dispatcher;
    btBroadphaseInterface*                   overlappingPairCache;
    btSequentialImpulseConstraintSolver*     solver;
    btDiscreteDynamicsWorld*                 dynamicsWorld;
    btAlignedObjectArray<btCollisionShape*>* collisionShapes;

  public:
    World(Terrain* terrain);
    ~World();
    void update();
};

#endif
