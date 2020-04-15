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
    std::thread world_thread;
    World* world;

  public:
    Server(int port);
    void start();
    void update();
    void update_player_events(const PlayerEvents& events);
    bool move_player(const PlayerProto& player);
    uint new_player(const NewPlayerRequest* req);
    void create_res(uint id, bool needs_position_set, PlayerUpdateResponse* res);
  private:
    static void start_update_loop(Server* server);
};

#endif
