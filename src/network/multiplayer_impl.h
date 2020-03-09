#ifndef _MULTIPLAYER_IMPL_H
#define _MULTIPLAYER_IMPL_H

#include "src/proto/multiplayer.grpc.pb.h"
#include <grpcpp/grpcpp.h>

class MultiplayerImpl final : public Multiplayer::Service {
  public:
    explicit MultiplayerImpl();
    grpc::Status UpdatePlayer(grpc::ServerContext* context, const PlayerUpdate* playerUpdate, PlayerUpdateResponse* feature) override;
};

#endif

