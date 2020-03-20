#include "server.h"
#include <string>
#include <iostream>
#include "multiplayer_impl.h"
#include <sstream>
#include <thread>
#include "world/world.h"
#include "proto_util.h"
#include <glm/gtx/string_cast.hpp>

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

  worldThread = thread(startUpdateLoop, this);
  worldThread.detach();

  unique_ptr<grpc::Server> server = builder.BuildAndStart();
  cout << "Listening on " << server_address << endl;
  server->Wait();

  cout << "Server stopped" << endl;
}

uint Server::newPlayer(const NewPlayerRequest* req) {
  uint id = world->addPlayer();
  return id;
}

bool Server::movePlayer(const PlayerProto& player) {
  uint id = player.id();
  bool playerExists = world->hasPlayer(id);
  if (!playerExists) {
    cout << "Player with invalid id " << id << " tried to move!" << endl;
    return false;
  }
  glm::mat4 transform = ProtoUtil::to_glm(player.transform());
  bool success = world->movePlayer(id, transform);
  if (!success) {
    return false;
  }
  cout << "Moving player" << endl << player.DebugString() << endl;
  return true;
}

void Server::update() {
  world->update();
}

void Server::startUpdateLoop(Server* server) {
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
