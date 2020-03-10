#include "multiplayer_impl.h"
#include <grpcpp/grpcpp.h>
#include <string>

using namespace std;

MultiplayerImpl::MultiplayerImpl(Server* server) {
  this->server = server;
}

grpc::Status MultiplayerImpl::UpdatePlayer(grpc::ServerContext* context, const PlayerUpdate* req, PlayerUpdateResponse* res) {
  server->movePlayer(req->player());
  return grpc::Status::OK;
}

