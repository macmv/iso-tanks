#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "world/world.h"
#include "models/scene_manager.h"

using namespace std;

class Projectile {
  protected:
    float speed;
  private:
    Scene* scene = NULL;

  public:
    Projectile(ShootEvent event, btRigidBody* body, SceneManager* scene_manager);
    Projectile(ShootEvent event, btRigidBody* body);
    float get_speed();
    Scene* get_scene();
  private:
    virtual string get_scene_name();
};

#endif

