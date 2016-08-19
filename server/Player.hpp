#pragma once
#include <memory>
#include "GameServer.hpp"

namespace sfio {
class QuadTree;
class GameServer;
class Player {
  GameServer::Client *client;
  QuadTree *room;

 public:
  Player(GameServer::Client *cl, QuadTree *room) : client(cl), room(room) {}
};
}
