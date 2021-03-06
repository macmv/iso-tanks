#include "server_world.h"
#include "opengl/camera.h"
#include "player/player.h"
#include "player/projectile/missile.h"
#include "network/proto_util.h"
#include "player/settings/controller.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <cmath>
#include "debug.h"
#include <time.h>
#include <unordered_map>
#include <chrono>
#include <reactphysics3d/reactphysics3d.h>

using namespace std;

ServerWorld::ServerWorld(Terrain* terrain) {

  rp3d::TriangleVertexArray* vertexArray = new rp3d::TriangleVertexArray(
      terrain->vertices->size(), terrain->vertices->data(), sizeof(glm::vec3),
                                 terrain->normals->data(), sizeof(glm::vec3),
      terrain->indices->size() / 3, terrain->indices->data(), 3 * sizeof(uint),
      rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
      rp3d::TriangleVertexArray::NormalDataType::NORMAL_FLOAT_TYPE,
      rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

  rp3d::TriangleMesh* mesh = physics.createTriangleMesh();

  mesh->addSubpart(vertexArray);

  world_shape = physics.createConcaveMeshShape(mesh);
  player_box_shape = physics.createBoxShape(rp3d::Vector3(1, 1, 1));
  player_capsule_shape = physics.createCapsuleShape(1, 1.5);
  missile_shape = physics.createCapsuleShape(1, 1);

  rp3d::RigidBody* body = add_body(glm::mat4(1));
  body->addCollider(world_shape, rp3d::Transform::identity());
  body->setType(rp3d::BodyType::STATIC);

  //  world->setIsDebugRenderingEnabled(true);
  //  rp3d::DebugRenderer& render = world->getDebugRenderer();
  //  debug_render = new DebugRender(render);

  prev_update = chrono::high_resolution_clock::now();

  srand(time(0));
}

ServerWorld::~ServerWorld() {
  // for (int i = dynamics_world->getNumCollisionObjects() - 1; i >= 0; i--) {
  //   rp3d::CollisionShape* obj = dynamics_world->getCollisionObjectArray()[i];
  //   rp3d::RigidBody* body = btRigidBody::upcast(obj);
  //   if (body && body->getMotionState()) {
  //     delete body->getMotionState();
  //   }
  //   dynamics_world->removeCollisionObject(obj);
  //   delete obj;
  // }
}

uint ServerWorld::add_player() {
  uint id = (uint) rand();
  rp3d::RigidBody* body = add_body(glm::translate(glm::mat4(1), glm::vec3(0, -970, 0)));
  body->addCollider(player_box_shape, rp3d::Transform::identity());
  body->updateMassPropertiesFromColliders();

  Player* player = new Player(body, scene_manager);
  players.insert({id, player});
  return id;
}

bool ServerWorld::has_player(uint id) {
  return players.find(id) != players.end();
}

Player ServerWorld::get_player(uint id) {
  assert(has_player(id));
  return *players.at(id);
}

bool ServerWorld::move_player(uint id, glm::mat4 transform) {
  Player* p = players.at(id);
  p->set_transform(transform);
  return true;
}

void ServerWorld::force_physics_update() {
  cout << "Forcing physics update!" << endl;
  world->update((double) PHYSICS_STEP / 1000000000);
}

void ServerWorld::update() {

  // makes sure no one touches the world while stepping the simulation
  world_mutex.lock();

  cout << "----------------------------------------------" << endl;
  rp3d::RigidBody* body;
  for (size_t i = 0; i < bodies.size(); i++) {
    body = bodies.at(i);
    rp3d::Transform trans = body->getTransform();
    rp3d::Vector3 pos = trans.getPosition();
    rp3d::Quaternion q = trans.getOrientation();
    rp3d::Vector3 lin_vel = body->getLinearVelocity();
    rp3d::Vector3 ang_vel = body->getAngularVelocity();
    cout << "Object " << i << endl
      << "-- pos = (" << pos.x << ", " << pos.y << ", " << pos.z << ")," << endl
      << "-- orientation = (" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")," << endl
      << "-- linear vel = (" << lin_vel.x << ", " << lin_vel.y << ", " << lin_vel.z << ")," << endl
      << "-- angular vel = (" << ang_vel.x << ", " << ang_vel.y << ", " << ang_vel.z<< ")," << endl
      << "-- sleeping = " << (body->isSleeping() ? "true" : "false") << endl;
  }
  cout << "There are " << bodies.size() << " objects in the world" << endl;
  cout << "----------------------------------------------" << endl;

  chrono::high_resolution_clock::time_point update_time = chrono::high_resolution_clock::now();
  accumulator += (update_time - prev_update).count();
  prev_update = update_time;
  cout << "Updating by " << (double) accumulator / 1000000000 << " seconds, or " << accumulator / PHYSICS_STEP << " times" << endl;
  while (accumulator > PHYSICS_STEP) {
    // world->update((double) PHYSICS_STEP / 1000000000);
    accumulator -= PHYSICS_STEP;
  }

  world_mutex.unlock();

  Player* player;
  for (pair<int, Player*> item : players) {
    player = item.second;
    glm::vec3 pos = glm::vec3(player->get_transform()[3]);
    pos = glm::normalize(pos) * 20.f;
    if (!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z)) {
      player->set_gravity(pos);
    }
    player->update();
  }

  Projectile* projectile;
  for (pair<int, Projectile*> item : projectiles) {
    projectile = item.second;
    glm::vec3 pos = glm::vec3(projectile->get_transform()[3]);
    pos = glm::normalize(pos) * 20.f;
    if (!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z)) {
      projectile->set_gravity(pos);
    }
    projectile->update();
  }
}

void ServerWorld::add_projectile(uint player_id, ProjectileProto proto) {
  if (scene_manager != NULL) {
    cerr << "Cannot add_projectile with player_id on client!" << endl;
    cerr << "Force exiting client" << endl;
    exit(1);
  }

  glm::mat4 transform = ProtoUtil::to_glm(proto.transform());
  // rotate upward vector to face the corrrect direction
  glm::vec3 vel = glm::vec3(transform * glm::vec4(0, 0, 1, 0));
  // make the projectile spawn in front of the player, not inside
  transform[3] = transform[3] + glm::vec4(vel * 5.5f, 0);
  // gotta go fast
  vel = vel * 200.f;

  rp3d::RigidBody* body = add_body(transform);
  body->addCollider(missile_shape, rp3d::Transform::identity());
  body->updateMassPropertiesFromColliders();

  uint id = (uint) rand();
  projectiles.insert({ id, new Missile(body) });
}

bool ServerWorld::has_projectile(uint id) {
  return projectiles.find(id) != projectiles.end();
}

rp3d::RigidBody* ServerWorld::add_body(glm::mat4 trans) {
  world_mutex.lock();

  rp3d::Transform transform = rp3d::Transform(rp3d::Vector3(trans[3][0], trans[3][1], trans[3][2]),
                                              rp3d::Matrix3x3(trans[0][0], trans[1][0], trans[2][0],
                                                              trans[0][1], trans[1][1], trans[2][1],
                                                              trans[0][2], trans[1][2], trans[2][2]));

  rp3d::Quaternion q = transform.getOrientation();
  q.normalize();
  transform.setOrientation(q);

  rp3d::RigidBody* body = world->createRigidBody(transform);

  bodies.push_back(body);

  world_mutex.unlock();

  return body;
}
