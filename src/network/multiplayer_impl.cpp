#include "multiplayer_impl.h"
#include <grpcpp/grpcpp.h>
#include <string>

using namespace std;

MultiplayerImpl::MultiplayerImpl(Server* server) {
  this->server = server;
}

grpc::Status MultiplayerImpl::UpdatePlayer(grpc::ServerContext* context, grpc::ServerReaderWriter<PlayerUpdateResponse, PlayerUpdate>* stream) {
  PlayerUpdateResponse res;
  PlayerUpdate update;
  while (stream->Read(&update)) {
    server->update_player_events(update.events());
    bool validPlayer = server->move_player(update.player());
    if (!validPlayer) {
      return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid player id");
    }
    server->create_res(update.player().id(), false, &res);
    stream->Write(res);
  }
  cout << "Connection with client closed" << endl;
  return grpc::Status::OK;
}

grpc::Status MultiplayerImpl::NewPlayer(grpc::ServerContext* context, const NewPlayerRequest* req, NewPlayerResponse* res) {
  int id = server->new_player(req);
  res->mutable_player()->set_id(id);
  return grpc::Status::OK;
}
