#ifndef _CONTROLLED_PLAYER_H
#define _CONTROLLED_PLAYER_H

#include "player.h"
#include "opengl/camera.h"
#include "models/scene_manager.h"
#include "settings/controller.h"
#include "event_list.h"
#include <reactphysics3d/reactphysics3d.h>

class ControlledPlayer final : public Player {
  private:
    glm::mat4 turret_start_transform;
    ModelInstance* turret_model = NULL;
    Controller* controller;

  public:
    ControlledPlayer(rp3d::RigidBody* body, Controller* controller, SceneManager* scene_manager, Camera* camera);
    void update();
    void update_events(EventList* events);
};

#endif
