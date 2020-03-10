#include "network/server.h"

using namespace std;

int main() {
  Server server = Server(8001);
  server.start();
}
