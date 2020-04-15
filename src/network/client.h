#ifndef _CLIENT_H
#define _CLIENT_H

#include "multiplayer_impl.h"
#include "world/world.h"
#include "player/controlled_player.h"
#include "player/event_list.h"
#include <thread>

class World;
class ControlledPlayer;

class Client {
  private:
    ControlledPlayer* player;
    std::unique_ptr<Multiplayer::Stub> stub;
    std::thread client_thread;
    uint id;
    World* world;
    PlayerUpdateResponse* recent_response;
    EventList* events;

  public:
    Client(World* world);
    void update_events(ControlledPlayer* player, bool didFire);
    void process_response();
  private:
    void send_update(std::shared_ptr<grpc::ClientReaderWriter<PlayerUpdate, PlayerUpdateResponse>> stream);
    bool send_new_player();
    std::shared_ptr<grpc::ClientReaderWriter<PlayerUpdate, PlayerUpdateResponse>> create_stream();
    static void start_update_loop(Client* client);
};

#endif
