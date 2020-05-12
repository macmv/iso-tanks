#include "world.h"
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
#include "reactphysics3d.h"

using namespace std;

World::World(Terrain* terrain, bool needs_debug) {

  // const ;
  // world = rp3d::DynamicsWorld(rp3d::Vector3(0, 0, 0), settings);

  rp3d::TriangleVertexArray* vertexArray = new rp3d::TriangleVertexArray(
      terrain->vertices->size(),
      terrain->vertices->data(), sizeof(glm::vec3),
      terrain->indices->size() / 3,
      terrain->indices->data(), 3 * sizeof(uint),
      rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
      rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);


  // Create the polyhedron mesh
  rp3d::TriangleMesh mesh;

  mesh.addSubpart(vertexArray);

  // Create the convex mesh collision shape
  rp3d::CollisionShape* shape = new rp3d::ConcaveMeshShape(&mesh);
  collision_shapes.insert({ "ground", shape });

  shape = new rp3d::BoxShape(rp3d::Vector3(1, .1, 1));
  collision_shapes.insert({ "player_box", shape });

  shape = new rp3d::CapsuleShape(1, 1.5);
  collision_shapes.insert({ "player_capsule", shape });

  shape = new rp3d::CapsuleShape(1, 1);
  collision_shapes.insert({ "missile", shape });

  vector<pair<string, rp3d::Transform>> shapes;
  shapes.push_back(make_pair("ground", rp3d::Transform::identity()));
  add_body(glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)), shapes, 1);
  // body->setFriction(.8);
  // body->setRollingFriction(.8);

  if (needs_debug) {
  //   debug_draw = new DebugDraw();
  //   debug_draw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
  //   dynamics_world->setDebugDrawer(debug_draw);
  }

  prev_update =
    std::chrono::system_clock::now().time_since_epoch() /
    std::chrono::milliseconds(1);

  this_player = NULL;

  srand(time(0));
}

World::~World() {
  // for (int i = dynamics_world->getNumCollisionObjects() - 1; i >= 0; i--) {
  //   rp3d::CollisionShape* obj = dynamics_world->getCollisionObjectArray()[i];
  //   rp3d::RigidBody* body = btRigidBody::upcast(obj);
  //   if (body && body->getMotionState()) {
  //     delete body->getMotionState();
  //   }
  //   dynamics_world->removeCollisionObject(obj);
  //   delete obj;
  // }

  for (pair<string, rp3d::CollisionShape*> items : collision_shapes) {
    rp3d::CollisionShape* shape = items.second;
    delete shape;
  }
  collision_shapes.clear();
}

World::World(Terrain* terrain, bool needs_debug, SceneManager* scene_manager, ParticleManager* particle_manager) : World(terrain, needs_debug) {
  this->scene_manager = scene_manager;
  this->particle_manager = particle_manager;
}

void World::draw_debug() {
}

void World::clean() {
}

void World::create_this_player(Controller* controller, Camera* camera) {
  vector<pair<string, rp3d::Transform>> shapes;
  shapes.push_back(make_pair("player_capsule", rp3d::Transform::identity()));
  shapes.push_back(make_pair("player_capsule", rp3d::Transform::identity()));
  rp3d::RigidBody* body = add_body(glm::translate(glm::mat4(1), glm::vec3(0, -1050, 0)), shapes, 1);

  this_player = new ControlledPlayer(body, controller, scene_manager, camera);
}

uint World::add_player() {
  uint id = (uint) rand();
  add_player(id);
  return id;
}

void World::add_player(uint id) {
  vector<pair<string, rp3d::Transform>> shapes;
  shapes.push_back(make_pair("player_capsule", rp3d::Transform::identity()));
  shapes.push_back(make_pair("player_capsule", rp3d::Transform::identity()));
  rp3d::RigidBody* body = add_body(glm::mat4(1), shapes, 1);

  Player* player = new Player(body, scene_manager);
  players->insert({id, player});
}

bool World::has_player(uint id) {
  return players->find(id) != players->end();
}

ControlledPlayer* World::get_this_player() {
  return this_player;
}

bool World::move_this_player(glm::mat4 transform) {
  this_player->set_transform(transform);
  return true;
}

bool World::move_player(uint id, glm::mat4 transform) {
  Player* p = players->at(id);
  p->set_transform(transform);
  return true;
}

void World::update_controls(float mouse_x_delta) {
  glm::vec3 pos = glm::vec3(this_player->get_transform()[3]);
  pos = glm::normalize(pos) * 20.f;
  if (!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z)) {
    this_player->set_gravity(pos);
  }
  this_player->update(mouse_x_delta);
}

void World::update() {

  // cout << "----------------------------------------------" << endl;
  // for (int j = dynamics_world->getNumCollisionObjects() - 1; j >= 0; j--) {
  //   btCollisionObject* obj = dynamics_world->getCollisionObjectArray()[j];
  //   btRigidBody* body = btRigidBody::upcast(obj);
  //   btTransform trans;
  //   if (body && body->getMotionState()) {
  //     body->getMotionState()->getWorldTransform(trans);
  //   } else {
  //     trans = obj->getWorldTransform();
  //   }
  //   printf("Object: %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
  // }
  // cout << "There are " << dynamics_world->getNumCollisionObjects() << " objects in the world" << endl;
  // cout << "----------------------------------------------" << endl;

  // makes sure no one touches the world while stepping the simulation
  world_mutex.lock();

  ulong update_time =
    std::chrono::system_clock::now().time_since_epoch() /
    std::chrono::milliseconds(1);
  world.update((double) (update_time - prev_update) / 1000);
  prev_update = update_time;

  world_mutex.unlock();

  Player* player;
  for (pair<int, Player*> item : *players) {
    player = item.second;
    glm::vec3 pos = glm::vec3(player->get_transform()[3]);
    pos = glm::normalize(pos) * 20.f;
    if (!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z)) {
      player->set_gravity(pos);
    }
    player->update();
  }

  Projectile* projectile;
  for (pair<int, Projectile*> item : *projectiles) {
    projectile = item.second;
    glm::vec3 pos = glm::vec3(projectile->get_transform()[3]);
    pos = glm::normalize(pos) * 20.f;
    if (!isnan(pos.x) && !isnan(pos.y) && !isnan(pos.z)) {
      projectile->set_gravity(pos);
    }
    projectile->update();
  }
}

// client function
void World::add_projectile(ProjectileProto proto) {
  if (scene_manager == NULL) {
    cerr << "Cannot add_projectile without player_id on server!" << endl;
    cerr << "Force exiting server" << endl;
    exit(1);
  }

  vector<pair<string, rp3d::Transform>> shapes;
  shapes.push_back(make_pair("missile", rp3d::Transform::identity()));
  rp3d::RigidBody* body = add_body(glm::mat4(1), shapes, .1f);

  glm::mat4 transform = ProtoUtil::to_glm(proto.transform());
  glm::vec3 vel = ProtoUtil::to_glm(proto.velocity());

  projectiles->insert({ proto.id(), new Missile(transform, vel, body, scene_manager, particle_manager) });
}

// server function
void World::add_projectile(uint player_id, ProjectileProto proto) {
  if (scene_manager != NULL) {
    cerr << "Cannot add_projectile with player_id on client!" << endl;
    cerr << "Force exiting client" << endl;
    exit(1);
  }

  vector<pair<string, rp3d::Transform>> shapes;
  shapes.push_back(make_pair("missile", rp3d::Transform::identity()));
  rp3d::RigidBody* body = add_body(glm::mat4(1), shapes, .1f);

  glm::mat4 transform = ProtoUtil::to_glm(proto.transform());
  // rotate upward vector to face the corrrect direction
  glm::vec3 vel = glm::vec3(transform * glm::vec4(0, 0, 1, 0));
  // make the projectile spawn in front of the player, not inside
  transform[3] = transform[3] + glm::vec4(vel * 1.5f, 0);
  // gotta go fast
  vel = vel * 200.f;

  uint id = (uint) rand();
  projectiles->insert({ id, new Missile(transform, vel, body) });
}

bool World::has_projectile(uint id) {
  return projectiles->find(id) != projectiles->end();
}

rp3d::RigidBody* World::add_body(glm::mat4 trans, vector<pair<string, rp3d::Transform>> shapes, float mass) {
  rp3d::Transform start_transform = rp3d::Transform(rp3d::Vector3(trans[3][0], trans[3][1], trans[3][2]),
                                                    rp3d::Matrix3x3(trans[0][1], trans[1][1], trans[2][1],
                                                                    trans[0][2], trans[1][2], trans[2][2],
                                                                    trans[0][3], trans[1][3], trans[2][3]));

  // makes sure no one is editing the world while we add a body
  world_mutex.lock();

  rp3d::RigidBody* body = world.createRigidBody(start_transform);
  for (pair<string, rp3d::Transform> shape : shapes) {
    body->addCollisionShape(collision_shapes.at(shape.first), shape.second, 1);
  }

  world_mutex.unlock();

  return body;
}
