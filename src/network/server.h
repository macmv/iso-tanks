#ifndef _SERVER_H
#define _SERVER_H

#include "src/proto/multiplayer.grpc.pb.h"
#include <string>
#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

class Server {
  private:
    int port;

  public:
    Server(int port);
    void start();
    void movePlayer(const PlayerProto& player);
};

#endif
