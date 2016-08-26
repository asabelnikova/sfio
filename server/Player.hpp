#pragma once
#include <memory>
#include "GameServer.hpp"

namespace sfio {
class QuadTree;
class Player {
  std::weak_ptr<GameServer::Client> client;
  std::shared_ptr<QuadTree> room;

 public:
  Player(std::weak_ptr<GameServer::Client> cl, std::shared_ptr<QuadTree> room)
      : client(cl), room(room) {}
};
}
