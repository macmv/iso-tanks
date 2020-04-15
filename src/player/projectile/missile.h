#ifndef _MISSILE_H
#define _MISSILE_H

#include "projectile.h"

class Missile : public Projectile {
  public:
    Missile(ProjectileProto proto, btRigidBody* body, SceneManager* scene_manager);
    Missile(ProjectileProto proto, btRigidBody* body);
};

#endif
