#include "multiplayer_impl.h"

grpc::Status UpdatePlayer(grpc::ServerContext* context, const PlayerUpdate* playerUpdate, PlayerUpdateResponse* feature) {
  return grpc::Status::OK;
}

