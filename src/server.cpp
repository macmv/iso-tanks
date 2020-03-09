#include "network/server.h"
#include <string>
#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

using namespace std;

int main() {
  Server server = Server(8001);
  server.start();
}
