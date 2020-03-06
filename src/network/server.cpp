#include "server.h"
#include "src/proto/multiplayer.pb.h"
#include <string>

using namespace std;

Server::Server(int port) {
  this->port = port;
  Player* player = new Player();
  cout << player->x() << endl;
}

