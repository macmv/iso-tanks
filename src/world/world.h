#ifndef _WORLD_H
#define _WORLD_H

#include "terrain/terrain.h"
#include "player/controlled_player.h"
#include "player/player.h"
#include "player/event/shoot_event.h"
#include "player/projectile/projectile.h"
#include "opengl/camera.h"
#include "debug.h"
#include "models/scene_manager.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <time.h>
#include <unordered_map>

class ControlledPlayer;
class Projectile;
class ParticleManager;

class World {
  private:
    btDefaultCollisionConfiguration*         collision_configuration;
    btCollisionDispatcher*                   dispatcher;
    btBroadphaseInterface*                   overlapping_pair_cache;
    btSequentialImpulseConstraintSolver*     solver;
    btDiscreteDynamicsWorld*                 dynamics_world;
    std::unordered_map<std::string, btCollisionShape*>*   collision_shapes = new std::unordered_map<std::string, btCollisionShape*>();
    DebugDraw*                                            debug_draw;
    clock_t                                               prev_update;
  public:
    std::unordered_map<uint, Player*>*       players = new std::unordered_map<uint, Player*>();
    std::unordered_map<uint, Projectile*>*   projectiles = new std::unordered_map<uint, Projectile*>();
    ControlledPlayer*                        this_player = NULL;
    std::vector<ModelInstance*>*             models = new std::vector<ModelInstance*>();
    SceneManager*                            scene_manager = NULL;
    ParticleManager*                         particle_manager = NULL;
    std::mutex                               world_mutex;

  public:
    World(Terrain* terrain, bool needs_debug);
    World(Terrain* terrain, bool needs_debug, SceneManager* scene_manager, ParticleManager* particle_manager);
    ~World();
    void create_this_player(Camera* camera);
    uint add_player();
    void add_player(uint id);
    bool has_player(uint id);
    bool move_player(uint id, glm::mat4 transform);
    bool move_this_player(glm::mat4 transform);
    // client function
    void add_projectile(ProjectileProto proto);
    // server function
    void add_projectile(uint player_id, ProjectileProto proto);
    bool has_projectile(uint id);
    void update_controls(float mouse_x_delta);
    void update();
    void draw_debug();
    void clean();
    ControlledPlayer* get_this_player();
  private:
    btRigidBody* add_body(glm::mat4 transform, string shape_name, float mass);
};

#endif
