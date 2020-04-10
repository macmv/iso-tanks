#ifndef _WORLD_H
#define _WORLD_H

#include "terrain/terrain.h"
#include "player/controlled_player.h"
#include "player/player.h"
#include "opengl/camera.h"
#include "debug.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <time.h>
#include <unordered_map>

class ControlledPlayer;

class World {
  private:
    btDefaultCollisionConfiguration*         collisionConfiguration;
    btCollisionDispatcher*                   dispatcher;
    btBroadphaseInterface*                   overlappingPairCache;
    btSequentialImpulseConstraintSolver*     solver;
    btDiscreteDynamicsWorld*                 dynamicsWorld;
    std::vector<btCollisionShape*>*          collisionShapes;
    DebugDraw* debugDraw;
    clock_t prev_update;
  public:
    std::unordered_map<uint, Player*>*       players;
    ControlledPlayer*                        thisPlayer;
    std::vector<ModelInstance*>*             models;

  public:
    World(Terrain* terrain, bool needsTerrain);
    ~World();
    void createThisPlayer(Camera* camera);
    uint addPlayer();
    void addPlayer(uint id);
    bool hasPlayer(uint id);
    bool movePlayer(uint id, glm::mat4 transform);
    bool moveThisPlayer(glm::mat4 transform);
    void updateControls(float mouseXDelta);
    void update();
    void drawDebug();
    void clean();
    ControlledPlayer* getPlayer();
};

#endif
