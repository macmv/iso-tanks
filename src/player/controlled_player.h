#ifndef _CONTROLLED_PLAYER_H
#define _CONTROLLED_PLAYER_H

#include "player.h"
#include "opengl/camera.h"

class ControlledPlayer final : public Player {
  private:
    glm::mat4 turretTransform;
    Camera* camera;

  public:
    ControlledPlayer(btRigidBody* body, Camera* camera);
    void update(float mouseXDelta);
};

#endif
