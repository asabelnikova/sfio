#pragma once
#include <glm/vec2.hpp>
#include <list>
#include <memory>
#include "Client.hpp"
#include "Player.hpp"
#include "QuadTree.hpp"
namespace sfio {
class GameField : public std::enable_shared_from_this<GameField> {
  std::shared_ptr<QuadTree> index;
  std::unordered_map<uint64_t, std::shared_ptr<Player>> players;
  const int MAX_COUNT_PER_ROOM = 500;

 public:
  using Players = std::unordered_map<uint64_t, std::shared_ptr<Player>>;
  std::shared_ptr<Player> spawn(std::shared_ptr<GameServer::Client>);
  void updateParameters(double timestamp);
  bool isOvercrowded();
  const std::unordered_map<uint64_t, std::shared_ptr<Player>>& getPlayers();
  GameField(std::shared_ptr<QuadTree> q, Players&& pl)
      : index(q), players(pl){};
};
}
