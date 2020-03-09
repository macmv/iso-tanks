#ifndef _CLIENT_H
#define _CLIENT_H

#include "player/player.h"

class Player;

class Client {
  private:
    Player* player;

  public:
    Client(Player* player);
    void update();
    void shoot();
};

#endif
