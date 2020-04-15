#ifndef _MISSILE_H
#define _MISSILE_H

#include "projectile.h"

class Missile : public Projectile {
  public:
    Missile(ShootEvent event, btRigidBody* body, SceneManager* scene_manager);
    Missile(ShootEvent event, btRigidBody* body);
};

#endif
