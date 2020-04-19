#include "missile.h"

Missile::Missile(glm::mat4 transform,
    glm::vec3 velocity,
    btRigidBody* body,
    SceneManager* scene_manager) : Projectile(transform,
      velocity,
      body,
      scene_manager,
      new ParticleCloud(100, 0.1f, 1, new Material(glm::vec3(1, 1, 0)), "src/shader/circle_particle"),
      "assets/missile.glb") {

}

Missile::Missile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body) : Projectile(transform, velocity, body) {

}
