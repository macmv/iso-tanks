#include "server.h"
#include <string>
#include <iostream>
#include "multiplayer_impl.h"
#include <sstream>
#include <thread>
#include "world/server_world.h"
#include "proto_util.h"
#include <glm/gtx/string_cast.hpp>
#include "player/event/shoot_event.h"

using namespace std;

Server::Server(int port) {
  this->port = port;
  cout << "Starting world generation..." << endl;
  Terrain* terrain = new Terrain(100);
  world = new ServerWorld(terrain);
  cout << "World generation finished" << endl;
}

void Server::start() {
  cout << "Server starting..." << endl;

  string server_address = "0.0.0.0:" + to_string(port);
  MultiplayerImpl service(this);

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  world_thread = thread(start_update_loop, this);
  world_thread.detach();

  unique_ptr<grpc::Server> server = builder.BuildAndStart();
  cout << "Listening on " << server_address << endl;

  server->Wait();

  cout << "Server stopped" << endl;
}

// called whenever the client sends in an update. This should be called 20 times a second
void Server::update_player(const PlayerUpdate& update) {
  cached_events.insert({update.player().id(), update});
}

// called 20 times per second. Will send updates to all players
void Server::tick() {
  unordered_set<uint> invalid_moves;
  unordered_set<uint> valid_moves;
  for (auto item : cached_events) {
    uint id = item.first;
    if (!has_connection(id)) {
      continue;
    }
    const PlayerUpdate& update = item.second;
    const PlayerProto& player = update.player();
    assert(world->has_player(id));
    if (update.events().shoot().exists()) {
      world->add_projectile(player.id(), update.events().shoot().projectile());
    }
    glm::mat4 transform = ProtoUtil::to_glm(player.transform());
    bool success = world->move_player(id, transform);
    if (!success) {
      invalid_moves.insert(id);
    } else {
      valid_moves.insert(id);
    }
  }
  cached_events.clear();
  world->update();
  PlayerUpdateResponse res;
  for (auto item : connections) {
    uint id = item.first;
    auto stream = item.second;
    res.clear_player();
    // tells the client about all other players that moved
    for (uint other_id : valid_moves) {
      if (other_id == id) {
        continue;
      }
      Player player = world->get_player(other_id);
      PlayerProto* proto = res.add_player();
      ProtoUtil::to_proto(proto, other_id, &player);
    }
    // sends the player back if the player made an invalid move
    if (invalid_moves.find(id) != invalid_moves.end()) {
      Player player = world->get_player(id);
      PlayerProto* proto = res.add_player();
      ProtoUtil::to_proto(proto, id, &player);
    }
    // removing projectiles for initial testing of the new system
    // res->clear_projectile();
    // for (std::pair<uint, Projectile*> item : *world->projectiles) {
    //   ProjectileProto* proto = res->add_projectile();
    //   ProtoUtil::to_proto(proto, item.first, item.second);
    // }
    stream->Write(res);
  }
}

// called when a player connects for the first time
uint Server::add_player(const NewPlayerRequest* request) {
  uint id = world->add_player();
  return id;
}

// called once the player has registered itself, and has sent it's first update packet
void Server::add_connection(uint id, grpc::ServerReaderWriter<PlayerUpdateResponse, PlayerUpdate>* stream) {
  assert(connections.find(id) == connections.end());
  assert(world->has_player(id));
  connections.insert({id, stream});
}

// called after a player disconnects, and is closing the connection
void Server::remove_connection(uint id) {
  assert(connections.find(id) != connections.end());
  connections.erase(id);
}

// checks if the player has a connection open
bool Server::has_connection(uint id) {
  return connections.find(id) != connections.end();
}

// checks if the player has registered itself yet
bool Server::has_player(uint id) {
  return world->has_player(id);
}

void Server::start_update_loop(Server* server) {
  cout << "World update loop started" << endl;
  struct timespec tim, tim2;
  tim.tv_sec = 0;
  // 20 updates per second
  tim.tv_nsec = 50000000;
  while(1) {
    nanosleep(&tim, &tim2);
    server->tick();
  }
}
