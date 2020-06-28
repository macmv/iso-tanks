#ifndef _CLIENT_WORLD_H
#define _CLIENT_WORLD_H

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

class ClientWorld {
  private:
    const uint                             PHYSICS_STEP = 20000000;
    rp3d::PhysicsCommon                    physics;
    rp3d::PhysicsWorld*                    world = physics.createPhysicsWorld();
    rp3d::ConcaveMeshShape*                world_shape = NULL;
    rp3d::BoxShape*                        player_box_shape = NULL;
    rp3d::CapsuleShape*                    player_capsule_shape = NULL;
    rp3d::CapsuleShape*                    missile_shape = NULL;
    std::vector<rp3d::RigidBody*>          bodies;
    uint                                   accumulator = 0;
    chrono::high_resolution_clock::time_point prev_update;
    std::vector<ModelInstance*>*           models = new std::vector<ModelInstance*>();
    SceneManager*                          scene_manager = NULL;
    ParticleManager*                       particle_manager = NULL;
    std::mutex                             world_mutex;
    DebugRender*                           debug_render = NULL;
  public:
    ControlledPlayer*                      this_player = NULL;
    std::unordered_map<uint, Projectile*>* projectiles = new std::unordered_map<uint, Projectile*>();
    std::unordered_map<uint, Player*>*     players = new std::unordered_map<uint, Player*>();

  public:
    ClientWorld(Terrain* terrain, bool needs_debug, SceneManager* scene_manager, ParticleManager* particle_manager);
    ~ClientWorld();
    void create_this_player(Controller* controller, Camera* camera);
    void add_player(uint id);
    bool has_player(uint id);
    bool move_player(uint id, glm::mat4 transform);
    bool move_this_player(glm::mat4 transform);
    void add_projectile(ProjectileProto proto);
    bool has_projectile(uint id);
    void update_controls();
    void force_physics_update();
    void update();
    void draw_debug();
    ControlledPlayer* get_this_player();
  private:
    rp3d::RigidBody* add_body(glm::mat4 transform);
};

#endif
