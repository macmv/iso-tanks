#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "../../models/model_instance.h"

class Terrain {
  public:
    ModelInstance* instance;

  public:
    Terrain(int detail);
    int detail;
};

#endif
