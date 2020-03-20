#ifndef _PROTO_UTIL_H
#define _PROTO_UTIL_H

#include "src/proto/multiplayer.grpc.pb.h"
#include <glm/glm.hpp>
#include "player/player.h"

class ProtoUtil {
  public:
    static glm::mat4 to_glm(Transform trans);
    static void to_proto(PlayerProto* proto, uint id, Player* player);
};

#endif
