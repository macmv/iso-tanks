#include "missile.h"

Missile::Missile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body, SceneManager* scene_manager) : Projectile(transform, velocity, body, scene_manager, "assets/missile.glb") {

}

Missile::Missile(glm::mat4 transform, glm::vec3 velocity, btRigidBody* body) : Projectile(transform, velocity, body) {

}
