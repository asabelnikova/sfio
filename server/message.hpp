#pragma once
#include <stdint.h>
#include "gamemessage.pb.h"

enum MessageType : uint8_t {
  Handshake = gamemessages::IncomingMessage::HANDSHAKE,
  Spawn = gamemessages::IncomingMessage::SPAWN,
  Thrust = gamemessages::IncomingMessage::THRUST,
  Shoot = gamemessages::IncomingMessage::SHOOT
};

struct MessageBase {
  virtual ~MessageBase(){};
};

template <typename T>
struct Message : public MessageBase {
  T data;
  Message(T &&t) : T(std::forward<T>(t)){};
};

// typedef Message<gamemessages::Thrust>
// ThrustMessage;
// typedef Message<gamemessages::Shoot> ShootMessage;
// typedef Message<gamemessages::Handshake> HandshakeMessage;
// typedef Message<gamemessages::Spawn> SpawnMessage;
