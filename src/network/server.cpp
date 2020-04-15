#include "server.h"
#include <string>
#include <iostream>
#include "multiplayer_impl.h"
#include <sstream>
#include <thread>
#include "world/world.h"
#include "proto_util.h"
#include <glm/gtx/string_cast.hpp>
#include "player/event/shoot_event.h"

using namespace std;

Server::Server(int port) {
  this->port = port;
  cout << "Starting world generation..." << endl;
  Terrain* terrain = new Terrain(100);
  world = new World(terrain, false);
  cout << "World generation finished" << endl;
}

void Server::start() {
  cout << "Server starting..." << endl;

  string server_address = "0.0.0.0:" + to_string(port);
  MultiplayerImpl service(this);

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  world_thread = thread(start_update_loop, this);
  world_thread.detach();

  unique_ptr<grpc::Server> server = builder.BuildAndStart();
  cout << "Listening on " << server_address << endl;
  server->Wait();

  cout << "Server stopped" << endl;
}

uint Server::new_player(const NewPlayerRequest* req) {
  uint id = world->add_player();
  return id;
}

void Server::update_player_events(const PlayerEvents& events) {
  if (events.shoot().exists()) {
    world->add_projectile(ShootEvent(events.shoot()));
  }
}

bool Server::move_player(const PlayerProto& player) {
  uint id = player.id();
  bool playerExists = world->has_player(id);
  if (!playerExists) {
    cout << "Player with invalid id " << id << " tried to move!" << endl;
    return false;
  }
  glm::mat4 transform = ProtoUtil::to_glm(player.transform());
  bool success = world->move_player(id, transform);
  if (!success) {
    return false;
  }
  return true;
}

// id is the id of the player this res is being sent to
void Server::create_res(uint id, bool needsPositionSet, PlayerUpdateResponse* res) {
  res->clear_player();
  for (std::pair<uint, Player*> pair : *world->players) {
    if (!(pair.first == id && !needsPositionSet)) {
      PlayerProto* proto = res->add_player();
      ProtoUtil::to_proto(proto, pair.first, pair.second);
    }
  }
}

void Server::update() {
  world->update();
}

void Server::start_update_loop(Server* server) {
  cout << "World update loop started" << endl;
  struct timespec tim, tim2;
  tim.tv_sec = 0;
  // 20 updates per second
  tim.tv_nsec = 50000000;
  while(1) {
    nanosleep(&tim, &tim2);
    server->update();
  }
}
