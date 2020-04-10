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
    std::thread clientThread;
    uint id;
    World* world;
    PlayerUpdateResponse* recentResponse;
    EventList* events;

  public:
    Client(World* world);
    void shoot();
    void processResponse();
  private:
    void sendUpdate(std::shared_ptr<grpc::ClientReaderWriter<PlayerUpdate, PlayerUpdateResponse>> stream);
    bool sendNewPlayer();
    std::shared_ptr<grpc::ClientReaderWriter<PlayerUpdate, PlayerUpdateResponse>> createStream();
    static void startUpdateLoop(Client* client);
};

#endif
