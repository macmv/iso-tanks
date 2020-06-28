#ifndef _SERVER_WORLD_H
#define _SERVER_WORLD_H

#include "terrain/terrain.h"
#include "player/controlled_player.h"
#include "player/player.h"
#include "player/event/shoot_event.h"
#include "player/projectile/projectile.h"
#include "player/settings/controller.h"
#include "opengl/camera.h"
#include "debug.h"
#include "models/scene_manager.h"
#include <time.h>
#include <unordered_map>
#include <reactphysics3d/reactphysics3d.h>

class ControlledPlayer;
class Projectile;
class ParticleManager;

class ServerWorld {
  private:
    const uint                                PHYSICS_STEP = 20000000;
    rp3d::PhysicsCommon                       physics;
    rp3d::PhysicsWorld*                       world = physics.createPhysicsWorld();
    rp3d::ConcaveMeshShape*                   world_shape = NULL;
    rp3d::BoxShape*                           player_box_shape = NULL;
    rp3d::CapsuleShape*                       player_capsule_shape = NULL;
    rp3d::CapsuleShape*                       missile_shape = NULL;
    std::vector<rp3d::RigidBody*>             bodies;
    uint                                      accumulator = 0;
    chrono::high_resolution_clock::time_point prev_update;
    std::vector<ModelInstance*>               models = std::vector<ModelInstance*>();
    SceneManager*                             scene_manager = NULL;
    ParticleManager*                          particle_manager = NULL;
    std::mutex                                world_mutex;
    std::unordered_map<uint, Projectile*>     projectiles = std::unordered_map<uint, Projectile*>();
    std::unordered_map<uint, Player*>         players = std::unordered_map<uint, Player*>();

  public:
    ServerWorld(Terrain* terrain);
    ~ServerWorld();
    uint add_player();
    void add_player(uint id);
    bool has_player(uint id);
    bool move_player(uint id, glm::mat4 transform);
    void add_projectile(uint player_id, ProjectileProto proto);
    bool has_projectile(uint id);
    void force_physics_update();
    void update();
    Player get_player(uint id);
  private:
    rp3d::RigidBody* add_body(glm::mat4 transform);
};

#endif
