#ifndef _WORLD_H
#define _WORLD_H

#include "terrain/terrain.h"
#include "../player/player.h"
#include "debug.h"
#include <bullet/btBulletDynamicsCommon.h>

class World {
  private:
    btDefaultCollisionConfiguration*         collisionConfiguration;
    btCollisionDispatcher*                   dispatcher;
    btBroadphaseInterface*                   overlappingPairCache;
    btSequentialImpulseConstraintSolver*     solver;
    btDiscreteDynamicsWorld*                 dynamicsWorld;
    btAlignedObjectArray<btCollisionShape*>* collisionShapes;
    DebugDraw* debugDraw;
  public:
    std::vector<Player*>*                    players;
    std::vector<ModelInstance*>*             models;

  public:
    World(Terrain* terrain);
    ~World();
    void add_player();
    void updateControls(float mouseXDelta);
    void update();
    void drawDebug();
    void clean();
    Player* getPlayer();
};

#endif
