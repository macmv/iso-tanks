#include "explosion.h"
#include "player/player.h"
#include <vector>

using namespace std;

void Explosion::explode(glm::vec3 position,
    float damage,
    float radius,
    vector<Player*> players,
    ExplosionProto* proto) {
  proto->set_id((uint) rand());
  proto->set_damage(damage);
  proto->set_radius(radius);
  for (Player* player : players) {
    player->damage(10);
  }
}

void Explosion::explode(ExplosionProto proto,
    ParticleManager* particle_manager) {
  particle_manager->add(new ParticleCloud(1, 1, 1, new Particle(5, .5, new Material(glm::vec3(.5, .5, .5))), "src/shader/circle_particle"));
}
