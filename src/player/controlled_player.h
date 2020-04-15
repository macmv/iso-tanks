#ifndef _CONTROLLED_PLAYER_H
#define _CONTROLLED_PLAYER_H

#include "player.h"
#include "opengl/camera.h"

class ControlledPlayer final : public Player {
  private:
    glm::mat4 turret_transform;

  public:
    ControlledPlayer(btRigidBody* body, Camera* camera);
    void update(float mouse_x_delta);
};

#endif
