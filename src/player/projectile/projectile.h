#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "world/world.h"
#include "models/scene_manager.h"
#include "src/proto/multiplayer.grpc.pb.h"

class Projectile {
  protected:
    float speed;
  private:
    Scene* scene = NULL;
    glm::mat4* transform;

  public:
    Projectile(ProjectileProto proto, btRigidBody* body, SceneManager* scene_manager, std::string scene_name);
    Projectile(ProjectileProto proto, btRigidBody* body);
    float get_speed();
    Scene* get_scene();
    glm::mat4 get_transform();
};

#endif

