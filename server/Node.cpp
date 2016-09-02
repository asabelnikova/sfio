#include "Node.hpp"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace sfio {

void Node::process(const ActionMessage *message){
  std::cout << "BCAST BACK" << message->data.id() <<"\n";
  gamemessages::OutcomingMessage omessage;
  omessage.set_type(gamemessages::OutcomingMessage_Type_Action);
  auto *act = new gamemessages::Action;
  act->CopyFrom(message->data);
  omessage.set_allocated_action(act);
  gameServer->sendToAllBut(message->client, omessage.SerializeAsString());
} 

void Node::process(const SpawnMessage* mes) {
  std::cout << "We must spawn player in gamefield, but we will do this later\n";
  gamemessages::OutcomingMessage message;
  message.set_type(gamemessages::OutcomingMessage_Type_PlayerState);
  auto ps = message.mutable_playerstate();
  auto now = std::chrono::system_clock::now();
  auto time_since_epoch = now.time_since_epoch();
  double millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch)
          .count();
  gamemessages::Parameter energy;
  gamemessages::Parameter position;
  energy.mutable_scalar()->set_v(100);
  energy.mutable_scalar()->set_dv(0);
  position.mutable_vec2()->mutable_v()->set_x(0);
  position.mutable_vec2()->mutable_v()->set_y(0);
  position.mutable_vec2()->mutable_dv()->set_x(0);
  position.mutable_vec2()->mutable_dv()->set_y(0);

  (*ps->mutable_parameters())["energy"] = energy;
  (*ps->mutable_parameters())["position"] = position;

  ps->set_isalive(true);
  mes->client->send(message.SerializeAsString());
}
inline void Node::findRoomForPlayer(
    std::shared_ptr<GameServer::Client> client) noexcept {
  auto roomIt =
      std::find_if(std::cbegin(rooms), std::cend(rooms), [&](auto& r) {
        auto shared = r.lock();
        if (!shared) return false;
        return shared->count() < MAX_COUNT_PER_ROOM;
      });
  if (roomIt == rooms.end()) {
    auto shared = std::make_shared<QuadTree>();
    rooms.push_back(shared);
    players.push_back(Player(client, shared));
  } else {
    auto shared = roomIt->lock();
    if (shared)
      players.push_back(Player(client, shared));
    else {
      std::cerr << __FILE__ << ":" << __LINE__
                << ": Almost impossible case, when we doing strange things\n";
      shared = std::make_shared<QuadTree>();
      rooms.push_back(shared);
      players.push_back(Player(client, shared));
    }
  }
}
void Node::process(const HandshakeMessage* mes) {
  auto now = std::chrono::system_clock::now();
  auto time_since_epoch = now.time_since_epoch();
  double millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch)
          .count();
  auto username = mes->data.name();
  findRoomForPlayer(mes->client);
  std::stringstream ss;
  ss << mes->client->getId();
  gamemessages::OutcomingMessage message;
  message.set_type(gamemessages::OutcomingMessage_Type_HandshakeResponse);
  message.mutable_handshakeresponse()->set_id(ss.str());
  message.mutable_handshakeresponse()->set_zerotime(millis);
  mes->client->send(message.SerializeAsString());
}
}
