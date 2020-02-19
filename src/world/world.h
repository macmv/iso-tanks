#ifndef _WORLD_H
#define _WORLD_H

#include "terrain/terrain.h"

class World {
  public:
    World(Terrain* terrain);
    void update();
};

#endif
