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

grpc::Status MultiplayerImpl::NewPlayer(grpc::ServerContext* context, const PlayerAddRequest* req, PlayerAddResponse* res) {
  int id = server->addPlayer(req);
  res->mutable_player()->set_id(id);
  return grpc::Status::OK;
}
