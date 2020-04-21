#ifndef _MISSILE_H
#define _MISSILE_H

#include "projectile.h"
#include "opengl/particle/particle_cloud.h"

class Missile : public Projectile {
  private:
    ParticleCloud* cloud;

  public:
    Missile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body, SceneManager* scene_manager, ParticleManager* particle_manager);
    Missile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body);
    void update() override;
};

#endif
