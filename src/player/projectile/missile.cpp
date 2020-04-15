#include "missile.h"

Missile::Missile(ProjectileProto proto, btRigidBody* body, SceneManager* scene_manager) : Projectile(proto, body, scene_manager, "assets/missile.glb") {

}

Missile::Missile(ProjectileProto proto, btRigidBody* body) : Projectile(proto, body) {

}
