#ifndef _PROTO_UTIL_H
#define _PROTO_UTIL_H

#include "src/proto/multiplayer.grpc.pb.h"
#include <glm/glm.hpp>
#include "player/player.h"
#include "player/projectile/projectile.h"

class ProtoUtil {
  public:
    static glm::mat4 to_glm(Transform trans);
    static glm::vec3 to_glm(Transform::Vector3 vec);
    static void to_proto(glm::mat4 transform, Transform* proto);
    static void to_proto(glm::vec3 vec, Transform::Vector3* proto);
    static void to_proto(PlayerProto* proto, uint id, Player* player);
    static void to_proto(ProjectileProto* proto, uint id, Projectile* projectile);
};

#endif
