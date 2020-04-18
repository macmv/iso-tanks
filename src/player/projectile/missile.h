#ifndef _MISSILE_H
#define _MISSILE_H

#include "projectile.h"

class Missile : public Projectile {
  public:
    Missile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body, SceneManager* scene_manager);
    Missile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body);
};

#endif
