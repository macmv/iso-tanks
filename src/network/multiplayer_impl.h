
#ifndef _MULTIPLAYER_IMPL_H
#define _MULTIPLAYER_IMPL_H

#include "src/proto/multiplayer.grpc.pb.h"
#include <grpc/grpc.h>

class MultiplayerImpl final : public Multiplayer::Service {
  void UpdatePlayer();
  grpc::Status UpdatePlayer(grpc::ServerContext* context, const PlayerUpdate* playerUpdate, PlayerUpdateResponse* feature);
};

#endif

