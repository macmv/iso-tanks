#include "client.h"
#include "player/player.h"
#include "multiplayer_impl.h"
#include <iostream>

using namespace std;

Client::Client(Player* player) {
  this->player = player;
  stub = Multiplayer::NewStub(
    grpc::CreateChannel("localhost:8001",
                        grpc::InsecureChannelCredentials()));
}

void Client::update() {
  cout << "Updating client" << endl;
  grpc::ClientContext context;

  PlayerUpdate update;
  update.mutable_player()->set_x(2);
  update.mutable_player()->set_y(3);
  PlayerUpdateResponse res;
  stub->UpdatePlayer(&context, (const PlayerUpdate&) update, &res);
}

