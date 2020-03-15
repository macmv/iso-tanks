#include "multiplayer_impl.h"
#include <grpcpp/grpcpp.h>
#include <string>

using namespace std;

MultiplayerImpl::MultiplayerImpl(Server* server) {
  this->server = server;
}

grpc::Status MultiplayerImpl::UpdatePlayer(grpc::ServerContext* context, const PlayerUpdate* req, PlayerUpdateResponse* res) {
  bool validPlayer = server->movePlayer(req->player());
  if (validPlayer) {
    return grpc::Status::OK;
  } else {
    return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid player id");
  }
}

grpc::Status MultiplayerImpl::NewPlayer(grpc::ServerContext* context, const NewPlayerRequest* req, NewPlayerResponse* res) {
  int id = server->newPlayer(req);
  res->mutable_player()->set_id(id);
  return grpc::Status::OK;
}
