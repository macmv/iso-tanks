#include "client.h"
#include "player/controlled_player.h"
#include "multiplayer_impl.h"
#include <iostream>
#include <thread>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "proto_util.h"
#include "player/event_list.h"

using namespace std;

Client::Client(World* world) {
  this->player = world->this_player;
  this->world = world;
  stub = Multiplayer::NewStub(
    grpc::CreateChannel("localhost:8001",
                        grpc::InsecureChannelCredentials()));
  id = 0;
  client_thread = thread(start_update_loop, this);
  client_thread.detach();
  recent_response = NULL;
  events = new EventList();
}

void Client::update_events(ControlledPlayer* player, bool didFire) {
  if (didFire) {
    events->shoot(player);
  }
}

void Client::send_update(std::shared_ptr<grpc::ClientReaderWriter<PlayerUpdate, PlayerUpdateResponse>> stream) {
  PlayerUpdate update;
  ProtoUtil::to_proto(update.mutable_player(), id, player);
  events->to_proto(update.mutable_events());
  PlayerUpdateResponse* res = new PlayerUpdateResponse();
  stream->Write(update);
  stream->Read(res);
  this->recent_response = res;
}

void Client::process_response() {
  if (recent_response == NULL) {
    return;
  }
  for (PlayerProto proto : recent_response->player()) {
    if (id == proto.id()) {
      world->move_this_player(ProtoUtil::to_glm(proto.transform()));
    } else {
      if (!world->has_player(proto.id())) {
        world->add_player(proto.id());
      }
      world->move_player(proto.id(), ProtoUtil::to_glm(proto.transform()));
    }
  }
  recent_response = NULL;
}

bool Client::send_new_player() {
  grpc::ClientContext* context = new grpc::ClientContext();
  NewPlayerRequest req;
  NewPlayerResponse res;
  grpc::Status stat = stub->NewPlayer(context, (const NewPlayerRequest&) req, &res);
  if (stat.error_code() != grpc::StatusCode::OK) {
    cout << "Grpc new player request got error code " << stat.error_code() << endl;
    cout << "Message: " << stat.error_message() << endl;
    exit(1);
  }
  this->id = res.player().id();
  return true;
}

std::shared_ptr<grpc::ClientReaderWriter<PlayerUpdate, PlayerUpdateResponse>> Client::create_stream() {
  grpc::ClientContext* context = new grpc::ClientContext();
  return stub->UpdatePlayer(context);
}

void Client::start_update_loop(Client* client) {
  struct timespec tim, tim2;
  tim.tv_sec = 0;
  // 20 updates per second
  tim.tv_nsec = 50000000;
  bool success = client->send_new_player();
  if (!success) {
    cout << "Could not join server" << endl;
    return;
  }
  std::shared_ptr<grpc::ClientReaderWriter<PlayerUpdate, PlayerUpdateResponse>> stream = client->create_stream();
  while(1) {
    nanosleep(&tim, &tim2);
    client->send_update(stream);
  }
}

