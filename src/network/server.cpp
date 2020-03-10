#include "server.h"
#include <string>
#include <iostream>
#include "multiplayer_impl.h"
#include <sstream>

using namespace std;

Server::Server(int port) {
  this->port = port;
}

void Server::start() {
  cout << "Server starting..." << endl;

  string server_address = "0.0.0.0:" + to_string(port);
  MultiplayerImpl service(this);

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  unique_ptr<grpc::Server> server = builder.BuildAndStart();
  cout << "Listening on " << server_address << endl;
  server->Wait();

  cout << "Server stopped" << endl;
}

void Server::movePlayer(const PlayerProto& player) {
  cout << "Moving player to x " << player.x() << ", y " << player.y() << endl;
}
