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
  cout << "Connection with client opened" << endl;
  stream->Read(&update);
  uint id = update.player().id();
  if (server->has_connection(id)) {
    cout << "Player to connect with with an id already in use!" << endl;
    return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid player id");
  }
  if (!server->has_player(id)) {
    cout << "Player tried to connect with invalid player id!" << endl;
    return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid player id");
  }
  server->add_connection(id, stream);
  server->update_player(update);
  while (stream->Read(&update)) {
    if (server->has_connection(id) && server->has_player(id)) {
      server->update_player(update);
    } else {
      cout << "Player tried to connect with invalid player id!" << endl;
      return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid player id");
    }
  }
  server->remove_connection(id);
  cout << "Connection with client closed" << endl;
  return grpc::Status::OK;
}

grpc::Status MultiplayerImpl::NewPlayer(grpc::ServerContext* context, const NewPlayerRequest* req, NewPlayerResponse* res) {
  int id = server->add_player(req);
  res->mutable_player()->set_id(id);
  return grpc::Status::OK;
}
