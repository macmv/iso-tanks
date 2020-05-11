#ifndef _CONTROLLED_PLAYER_H
#define _CONTROLLED_PLAYER_H

#include "player.h"
#include "opengl/camera.h"
#include "models/scene_manager.h"
#include "settings/controller.h"
#include "event_list.h"

class ControlledPlayer final : public Player {
  private:
    glm::mat4 turret_transform;
    Controller* controller;

  public:
    ControlledPlayer(btRigidBody* body, Controller* controller, SceneManager* scene_manager, Camera* camera);
    void update(float mouse_x_delta);
    void update_events(EventList* events);
};

#endif
