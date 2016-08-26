#pragma once
#include <stdint.h>
#include "GameServer.hpp"
#include "gamemessage.pb.h"

namespace sfio {
enum MessageType : uint8_t {
  Handshake = gamemessages::IncomingMessage::HANDSHAKE,
  Spawn = gamemessages::IncomingMessage::SPAWN,
  Thrust = gamemessages::IncomingMessage::THRUST,
  Shoot = gamemessages::IncomingMessage::SHOOT
};

struct MessageProcessor;

struct MessageBase {
  std::shared_ptr<GameServer::Client> client;
  virtual ~MessageBase(){};
  virtual void process(MessageProcessor *) = 0;
};

template <typename T>
struct Message : public MessageBase {
  T data;
  Message(T &&t) : data(std::forward<T>(t)){};
  Message(const T &t) : data(t){};

 private:
  void process(MessageProcessor *p);
};

typedef Message<gamemessages::Action> ActionMessage;
typedef Message<gamemessages::Handshake> HandshakeMessage;
typedef Message<gamemessages::Spawn> SpawnMessage;
struct MessageProcessor {
  virtual void process(const ActionMessage *) = 0;
  virtual void process(const SpawnMessage *) = 0;
  virtual void process(const HandshakeMessage *) = 0;
  virtual ~MessageProcessor(){};
};

template <typename T>
void Message<T>::process(MessageProcessor *p) {
  p->process(this);
}
}
