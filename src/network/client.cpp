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
  this->player = world->thisPlayer;
  this->world = world;
  stub = Multiplayer::NewStub(
    grpc::CreateChannel("localhost:8001",
                        grpc::InsecureChannelCredentials()));
  id = 0;
  clientThread = thread(startUpdateLoop, this);
  clientThread.detach();
  recentResponse = NULL;
  events = new EventList();
}

void Client::updateEvents(ControlledPlayer* player, bool didFire) {
  if (didFire) {
    events->shoot(player);
  }
}

void Client::sendUpdate(std::shared_ptr<grpc::ClientReaderWriter<PlayerUpdate, PlayerUpdateResponse>> stream) {
  grpc::ClientContext* context = new grpc::ClientContext();

  PlayerUpdate update;
  ProtoUtil::to_proto(update.mutable_player(), id, player);
  events->toProto(update.mutable_events());
  PlayerUpdateResponse* res = new PlayerUpdateResponse();
  stream->Write(update);
  stream->Read(res);
  this->recentResponse = res;
}

void Client::processResponse() {
  if (recentResponse == NULL) {
    return;
  }
  for (PlayerProto proto : recentResponse->player()) {
    if (id == proto.id()) {
      world->moveThisPlayer(ProtoUtil::to_glm(proto.transform()));
    } else {
      if (!world->hasPlayer(proto.id())) {
        world->addPlayer(proto.id());
      }
      world->movePlayer(proto.id(), ProtoUtil::to_glm(proto.transform()));
    }
  }
  recentResponse = NULL;
}

bool Client::sendNewPlayer() {
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

std::shared_ptr<grpc::ClientReaderWriter<PlayerUpdate, PlayerUpdateResponse>> Client::createStream() {
  grpc::ClientContext* context = new grpc::ClientContext();
  return stub->UpdatePlayer(context);
}

void Client::startUpdateLoop(Client* client) {
  struct timespec tim, tim2;
  tim.tv_sec = 0;
  // 20 updates per second
  tim.tv_nsec = 50000000;
  bool success = client->sendNewPlayer();
  if (!success) {
    cout << "Could not join server" << endl;
    return;
  }
  std::shared_ptr<grpc::ClientReaderWriter<PlayerUpdate, PlayerUpdateResponse>> stream = client->createStream();
  while(1) {
    nanosleep(&tim, &tim2);
    client->sendUpdate(stream);
  }
}

