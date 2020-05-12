#ifndef _MISSILE_H
#define _MISSILE_H

#include "projectile.h"
#include "opengl/particle/particle_cloud.h"

class Missile : public Projectile {
  private:
    uint cloud_id;
    ParticleManager* particle_manager;

  public:
    Missile(glm::mat4 transform, glm::vec3 velocity, rp3d::RigidBody* body, SceneManager* scene_manager, ParticleManager* particle_manager);
    Missile(glm::mat4 transform, glm::vec3 velocity, rp3d::RigidBody* body);
    void update() override;
};

#endif
