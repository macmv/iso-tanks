#include "server.h"
#include <string>
#include <iostream>
#include "multiplayer_impl.h"
#include <sstream>
#include <thread>
#include "world/world.h"

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

int Server::newPlayer(const NewPlayerRequest* req) {
  return 4;
}

bool Server::movePlayer(const PlayerProto& player) {
  cout << "Moving player to " << player.DebugString() << endl;
  return player.id() == 4;
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
