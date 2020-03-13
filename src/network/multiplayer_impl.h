#ifndef _MULTIPLAYER_IMPL_H
#define _MULTIPLAYER_IMPL_H

#include "src/proto/multiplayer.grpc.pb.h"
#include "server.h"
#include <grpcpp/grpcpp.h>

class Server;

class MultiplayerImpl final : public Multiplayer::Service {
  private:
    Server* server;

  public:
    explicit MultiplayerImpl(Server* server);
    grpc::Status UpdatePlayer(grpc::ServerContext* context, const PlayerUpdate* req, PlayerUpdateResponse* res) override;
    grpc::Status NewPlayer(grpc::ServerContext* context, const PlayerAddRequest* req, PlayerAddResponse* res) override;
};

#endif
