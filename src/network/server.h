#ifndef _SERVER_H
#define _SERVER_H

#include "src/proto/multiplayer.grpc.pb.h"
#include <string>
#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <thread>
#include "world/world.h"

class World;

class Server {
  private:
    int port;
    std::thread worldThread;
    World* world;

  public:
    Server(int port);
    void start();
    void update();
    void updatePlayerEvents(const PlayerEvents& events);
    bool movePlayer(const PlayerProto& player);
    uint newPlayer(const NewPlayerRequest* req);
    void createRes(uint id, bool needsPositionSet, PlayerUpdateResponse* res);
  private:
    static void startUpdateLoop(Server* server);
};

#endif
