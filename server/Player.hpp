#pragma once
#include <memory>
#include "GameServer.hpp"
#include "Parameter.hpp"
#include "message.hpp"

namespace sfio {
class GameField;
class Player {
 public:
  using ParamMap = std::unordered_map<std::string, std::unique_ptr<Parameter>>;

 private:
  std::weak_ptr<GameServer::Client> client;
  std::shared_ptr<GameField> room;
  ParamMap parameters;

 public:
  void processAction(const ActionMessage *);
  void set(std::string, std::unique_ptr<Parameter> p);
  std::weak_ptr<GameServer::Client> getClient();
  const ParamMap &getParameters();
  Player(std::weak_ptr<GameServer::Client> cl, std::shared_ptr<GameField> room)
      : client(cl), room(room) {}
};
}
