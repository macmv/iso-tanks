class Server;

#ifndef _SERVER_H
#define _SERVER_H

#include "src/proto/multiplayer.grpc.pb.h"
#include <string>
#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <thread>

class Server {
  private:
    int port;
    std::thread worldThread;

  public:
    Server(int port);
    void start();
    void update();
    void movePlayer(const PlayerProto& player);
  private:
    static void startUpdateLoop(Server* server);
};

#endif
