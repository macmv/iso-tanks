#include "client.h"
#include "player/player.h"
#include "multiplayer_impl.h"
#include <iostream>
#include <thread>
#include <time.h>

using namespace std;

Client::Client(Player* player) {
  this->player = player;
  stub = Multiplayer::NewStub(
    grpc::CreateChannel("localhost:8001",
                        grpc::InsecureChannelCredentials()));
  clientThread = thread(startUpdateLoop, this);
  clientThread.detach();
}

void Client::sendUpdate() {
  grpc::ClientContext context;

  PlayerUpdate update;
  update.mutable_player()->mutable_transform()->mutable_position()->set_x(3);
  update.mutable_player()->mutable_transform()->mutable_position()->set_y(4);
  PlayerUpdateResponse res;
  stub->UpdatePlayer(&context, (const PlayerUpdate&) update, &res);
}

void Client::startUpdateLoop(Client* client) {
  struct timespec tim, tim2;
  tim.tv_sec = 0;
  // 20 updates per second
  tim.tv_nsec = 50000000;
  while(1) {
    nanosleep(&tim, &tim2);
    client->sendUpdate();
  }
}

