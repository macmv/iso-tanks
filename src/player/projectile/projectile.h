#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "world/world.h"
#include "models/scene_manager.h"
#include "src/proto/multiplayer.grpc.pb.h"
#include "opengl/render.h"

class ParticleCloud;
class Render;

class Projectile {
  protected:
    float speed;
    glm::mat4 transform;
  private:
    Scene* scene = NULL;
    glm::vec3 velocity;
    btRigidBody* body;

  public:
    Projectile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body, SceneManager* scene_manager, std::string scene_name);
    Projectile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body);
    virtual void update();
    float get_speed();
    Scene* get_scene();
    glm::mat4 get_transform();
    glm::vec3 get_velocity();
    void set_gravity(glm::vec3 gravity);
};

#endif

