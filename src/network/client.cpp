#include "client.h"
#include "player/player.h"
#include "multiplayer_impl.h"
#include <iostream>
#include <thread>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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
  glm::vec3 position = glm::vec3(player->scene->transform[3]);
  glm::quat rotation = glm::quat_cast(player->scene->transform);

  grpc::ClientContext context;

  PlayerUpdate update;
  update.mutable_player()->mutable_transform()->mutable_position()->set_x(position.x);
  update.mutable_player()->mutable_transform()->mutable_position()->set_y(position.y);
  update.mutable_player()->mutable_transform()->mutable_position()->set_z(position.z);
  update.mutable_player()->mutable_transform()->mutable_rotation()->set_x(rotation.x);
  update.mutable_player()->mutable_transform()->mutable_rotation()->set_y(rotation.y);
  update.mutable_player()->mutable_transform()->mutable_rotation()->set_z(rotation.z);
  update.mutable_player()->mutable_transform()->mutable_rotation()->set_w(rotation.w);
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

