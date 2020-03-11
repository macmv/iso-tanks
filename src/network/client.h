class Client;

#ifndef _CLIENT_H
#define _CLIENT_H

#include "multiplayer_impl.h"
#include "player/player.h"
#include <thread>

class Client {
  private:
    Player* player;
    std::unique_ptr<Multiplayer::Stub> stub;
    std::thread clientThread;

  public:
    Client(Player* player);
    void shoot();
  private:
    void sendUpdate();
    static void startUpdateLoop(Client* client);
};

#endif
