#include <list>
#include <memory>
#include "Client.hpp"
#include "QuadTree.hpp"
namespace sfio {
class Player {};
class Shoot {};
class GameField {
  std::unique_ptr<QuadTree> index;

 public:
  std::pair<int, int> getCommandsCount();
  Player spawn(Client);
  void kill(Player);
  std::list<Player*> shoot(Player, Shoot);  // return affected players
};
}
