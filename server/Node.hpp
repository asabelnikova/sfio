#pragma once
#include <memory>
#include "Client.hpp"
#include "GameServer.hpp"
#include "LobbyServer.hpp"
#include "Player.hpp"
#include "QuadTree.hpp"
#include "StateDumper.hpp"
namespace sfio {
class Node {
  typedef QuadTree Room;
  std::unique_ptr<GameServer> gameServer;
  std::unique_ptr<LobbyServer> lobbyServer;
  std::unique_ptr<StateDumper> stateDumper;
  std::vector<Room> rooms;
  std::vector<Client> clients;
  std::vector<Player> players;
};
}
