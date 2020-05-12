#ifndef _WORLD_H
#define _WORLD_H

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
#include <reactphysics3d.h>

class ControlledPlayer;
class Projectile;
class ParticleManager;

class World {
  private:
    rp3d::DynamicsWorld world = rp3d::DynamicsWorld(rp3d::Vector3(0, 10, 0), rp3d::WorldSettings());
    std::unordered_map<std::string, rp3d::CollisionShape*> collision_shapes = std::unordered_map<std::string, rp3d::CollisionShape*>();
    clock_t                                prev_update;
    std::vector<ModelInstance*>*           models = new std::vector<ModelInstance*>();
    SceneManager*                          scene_manager = NULL;
    ParticleManager*                       particle_manager = NULL;
    std::mutex                             world_mutex;
  public:
    ControlledPlayer*                      this_player = NULL;
    std::unordered_map<uint, Projectile*>* projectiles = new std::unordered_map<uint, Projectile*>();
    std::unordered_map<uint, Player*>*     players = new std::unordered_map<uint, Player*>();

  public:
    World(Terrain* terrain, bool needs_debug);
    World(Terrain* terrain, bool needs_debug, SceneManager* scene_manager, ParticleManager* particle_manager);
    ~World();
    void create_this_player(Controller* controller, Camera* camera);
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
    rp3d::RigidBody* add_body(glm::mat4 transform, vector<pair<string, rp3d::Transform>> shapes, float mass);
};

#endif
