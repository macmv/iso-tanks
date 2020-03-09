#include "network/multiplayer_impl.h"
#include <string>
#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

using namespace std;

int main() {
  cout << "Server starting..." << endl;

  std::string server_address = "0.0.0.0:8000";
  MultiplayerImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  unique_ptr<grpc::Server> server = builder.BuildAndStart();
  cout << "Listening on " << server_address << endl;
  server->Wait();

  cout << "Server stopped" << endl;
}
