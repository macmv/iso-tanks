#include <iostream>
#include "player/settings/settings.h"

using namespace std;

int main() {
  cout << "Test stuff here!" << endl;
  Settings* settings = new Settings();
  settings->load_defaults();
}
