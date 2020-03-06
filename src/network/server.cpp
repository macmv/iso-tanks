#include "server.h"
#include <string>
#include <iostream>
#include "multiplayer_impl.h"

using namespace std;

Server::Server(int port) {
  this->port = port;
  Player* player = new Player();
  cout << player->x() << endl;
}

