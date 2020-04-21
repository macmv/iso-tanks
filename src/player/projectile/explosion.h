#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include <glm/glm.hpp>
#include "src/proto/multiplayer.grpc.pb.h"
#include "player/player.h"
#include "opengl/particle/particle_manager.h"
#include <vector>

class Explosion {
  public:
    static void explode(glm::vec3 position,
        float damage,
        float radius,
        std::vector<Player*> players,
        ExplosionProto* proto);               // server function
    static void explode(ExplosionProto proto,
        ParticleManager* particle_manager);   // client function
};

#endif

