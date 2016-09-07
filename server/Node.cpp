#include "Node.hpp"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace sfio {

void Node::process(const ActionMessage* message) {
  gamemessages::OutcomingMessage omessage;
  omessage.set_type(gamemessages::OutcomingMessage_Type_Action);
  auto id = message->client->getId();
  if (players.count(id) > 0) players[id]->processAction(message);
  auto act = new gamemessages::Action;
  act->CopyFrom(message->data);
  omessage.set_allocated_action(act);
  gameServer->sendToAllBut(message->client, omessage.SerializeAsString());
}

void Node::process(const SpawnMessage* mes) {
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

  mes->client->send(message.SerializeAsString());
}
inline void Node::findRoomForPlayer(
    std::shared_ptr<GameServer::Client> client) noexcept {
  auto roomIt = std::find_if(std::begin(rooms), std::end(rooms), [](auto& r) {
    auto sh = r.lock();
    if (!sh) return false;
    return !sh->isOvercrowded();
  });
  if (roomIt == rooms.end()) {
    auto shared = std::make_shared<QuadTree>();
    auto gf = std::make_shared<GameField>(shared, GameField::Players());
    rooms.push_back(gf);
    players[client->getId()] = gf->spawn(client);

  } else {
    auto sh = roomIt->lock();
    players[client->getId()] = sh->spawn(client);
  }
}

void Node::clientDisconnected(std::shared_ptr<GameServer::Client> cl) {}
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
