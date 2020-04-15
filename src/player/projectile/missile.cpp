#include "missile.h"

Missile::Missile(ShootEvent event, btRigidBody* body, SceneManager* scene_manager) : Projectile(event, body, scene_manager, "assets/missile.glb") {

}

Missile::Missile(ShootEvent event, btRigidBody* body) : Projectile(event, body) {

}
