#include "GameField.hpp"
#include <chrono>
#include <glm/vec2.hpp>
#include "GameServer.hpp"
#include "Player.hpp"

namespace sfio {
bool GameField::isOvercrowded() { return index->count() > MAX_COUNT_PER_ROOM; }
std::shared_ptr<Player> GameField::spawn(
    std::shared_ptr<GameServer::Client> cl) {
  using v2 = glm::tvec2<double, glm::precision::highp>;
  using s = double;
  auto player = std::make_shared<Player>(cl, shared_from_this());
  v2 p{0.0, 0.0};
  v2 v{0.0, 0.0};
  double t = std::chrono::system_clock::now().time_since_epoch().count();

  player->set("position",
              std::unique_ptr<Parameter>(new TypedParameter<v2>{p, v, t}));
  player->set("mass",
              std::unique_ptr<Parameter>(new TypedParameter<s>{100, 0, t}));
  player->set("thrust",
              std::unique_ptr<Parameter>(new TypedParameter<s>{10, 0, t}));

  players[cl->getId()] = player;
  return player;
}
}
