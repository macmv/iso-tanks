#ifndef _CLIENT_H
#define _CLIENT_H

#include "multiplayer_impl.h"
#include "player/player.h"

class Player;

class Client {
  private:
    Player* player;
    std::unique_ptr<Multiplayer::Stub> stub;

  public:
    Client(Player* player);
    void update();
    void shoot();
};

#endif
