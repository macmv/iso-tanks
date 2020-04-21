#include "missile.h"

using namespace std;

Missile::Missile(glm::mat4 transform,
    glm::vec3 velocity,
    btRigidBody* body,
    SceneManager* scene_manager,
    ParticleManager* particle_manager) : Projectile(transform,
      velocity,
      body,
      scene_manager,
      "assets/missile.glb") {
  cloud = new ParticleCloud(1, 3, 1, new Particle(.5, .5, new Material(glm::vec3(1, 1, 0))), "src/shader/circle_particle");
  particle_manager->add(cloud);
}

Missile::Missile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body) : Projectile(transform, velocity, body) {

}

void Missile::update() {
  Projectile::update();
  if (cloud != NULL) {
    cloud->set_position(glm::vec3(transform[3]));
  }
}
