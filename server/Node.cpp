#include "Node.hpp"
#include <algorithm>
#include <sstream>

namespace sfio {
void Node::process(const SpawnMessage* mes) {
  std::cout << "We must spawn player in gamefield, but we will do this later\n";
  gamemessages::OutcomingMessage message;
  message.set_type(gamemessages::OutcomingMessage_Type_PlayerState);
  auto ps = message.mutable_playerstate();
  ps->set_energy(100.0);
  ps->set_isalive(true);
  mes->client->send(message.SerializeAsString());
}
void Node::process(const HandshakeMessage* mes) {
  auto username = mes->data.name();
  auto roomIt = std::find_if(rooms.begin(), rooms.end(), [&](auto& r) {
    return r->count() < MAX_COUNT_PER_ROOM;
  });
  if (roomIt == rooms.end()) {
    rooms.push_back(std::make_unique<QuadTree>());
    players.push_back(Player(mes->client, rooms.back().get()));
  } else
    players.push_back(Player(mes->client, roomIt->get()));
  std::stringstream ss;
  ss << mes->client->getId();
  gamemessages::OutcomingMessage message;
  message.set_type(gamemessages::OutcomingMessage_Type_HandshakeResponse);
  message.mutable_handshakeresponse()->set_id(ss.str());
  mes->client->send(message.SerializeAsString());
}
}
