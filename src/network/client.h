#ifndef _CLIENT_H
#define _CLIENT_H

#include "multiplayer_impl.h"
#include "player/controlled_player.h"
#include <thread>

class ControlledPlayer;

class Client {
  private:
    ControlledPlayer* player;
    std::unique_ptr<Multiplayer::Stub> stub;
    std::thread clientThread;

  public:
    Client(ControlledPlayer* player);
    void shoot();
  private:
    void sendUpdate();
    static void startUpdateLoop(Client* client);
};

#endif
