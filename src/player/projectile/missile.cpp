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
  ParticleCloud* cloud = new ParticleCloud(1, 3, 1, .5, new Particle(.5, .5, new Material(glm::vec3(1, 1, 0))), particle_manager->get_shader("src/shader/circle_particle"));
  this->cloud_id = particle_manager->add(cloud);
  this->particle_manager = particle_manager;
}

Missile::Missile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body) : Projectile(transform, velocity, body) {
  particle_manager = NULL;
}

void Missile::update() {
  Projectile::update();
  if (particle_manager != NULL) {
    ParticleCloud* cloud = particle_manager->get(cloud_id);
    if (cloud != NULL) {
     cloud->set_position(glm::vec3(transform[3]));
    }
  }
}
