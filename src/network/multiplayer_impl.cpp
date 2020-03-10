#include "multiplayer_impl.h"
#include <grpcpp/grpcpp.h>
#include <string>

using namespace std;

MultiplayerImpl::MultiplayerImpl() {

}

grpc::Status MultiplayerImpl::UpdatePlayer(grpc::ServerContext* context, const PlayerUpdate* req, PlayerUpdateResponse* res) {
  cout << "Got request: " << req << endl;
  return grpc::Status::OK;
}

