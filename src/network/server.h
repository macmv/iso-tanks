#ifndef _SERVER_H
#define _SERVER_H

#include "src/proto/multiplayer.grpc.pb.h"
#include <string>
#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include <thread>
#include "world/server_world.h"

class World;

class Server {
  private:
    int port;
    std::thread world_thread;
    ServerWorld* world;
    std::unordered_map<uint, grpc::ServerReaderWriter<PlayerUpdateResponse, PlayerUpdate>*> connections;
    std::unordered_map<uint, const PlayerUpdate&> cached_events;

  public:
    Server(int port);
    void start();
    void update_player(const PlayerUpdate& update);
    void tick();
    uint add_player(const NewPlayerRequest* request);
    void add_connection(uint id, grpc::ServerReaderWriter<PlayerUpdateResponse, PlayerUpdate>* stream);
    void remove_connection(uint id);
    bool has_connection(uint id);
    bool has_player(uint id);
  private:
    static void start_update_loop(Server* server);
};

#endif
