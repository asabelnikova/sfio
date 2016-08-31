#include "PacketFactory.hpp"
#include <iostream>
#include "gamemessage.pb.h"
#include "message.hpp"

namespace sfio {
std::unique_ptr<MessageBase> PacketFactory::create(const std::string &payload) {
  namespace gm = gamemessages;

  gm::IncomingMessage incomingMessage;
  incomingMessage.ParseFromString(payload);
  switch (incomingMessage.type()) {
    case gm::IncomingMessage::SPAWN: {
      std::cout << "just got a spawn packet\n";
      return std::make_unique<Message<gm::Spawn>>(incomingMessage.spawn());
    }
    case gm::IncomingMessage::ACTION: {
      std::cout << "just got a thrust packet\n";
      return std::make_unique<Message<gm::Action>>(incomingMessage.action());
    }
    case gm::IncomingMessage::HANDSHAKE: {
      std::cout << "just got a handshake packet\n";
      return std::make_unique<Message<gm::Handshake>>(incomingMessage.handshake());
    }
    default: { throw not_parsed; }
  }
}
}
