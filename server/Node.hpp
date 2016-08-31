#pragma once
#include <iostream>
#include <memory>
#include "GameServer.hpp"
#include "LobbyServer.hpp"
#include "Player.hpp"
#include "QuadTree.hpp"
#include "StateDumper.hpp"
#include "message.hpp"

namespace sfio {
class Node : public MessageProcessor {
  const int MAX_COUNT_PER_ROOM = 500;
  virtual void process(const ActionMessage *) { std::cout << " TH MES\n"; };
  virtual void process(const SpawnMessage *);
  virtual void process(const HandshakeMessage *);

  typedef std::weak_ptr<QuadTree> Room;  // shared between node and players;
  std::shared_ptr<GameServer>
      gameServer;  // whis server is shared between it's clients
  std::unique_ptr<LobbyServer> lobbyServer;
  std::unique_ptr<StateDumper> stateDumper;
  std::vector<Room> rooms;
  std::vector<Player> players;

  void messageRouter(std::shared_ptr<GameServer::Client> cl,
                     std::unique_ptr<MessageBase> &&msg) {
    msg->process(this);
  };
  inline void findRoomForPlayer(std::shared_ptr<GameServer::Client>) noexcept;

 public:
  Node(std::unique_ptr<GameServer> &&gs) : gameServer(std::move(gs)) {
    gameServer->onMessage([&](std::shared_ptr<GameServer::Client> cl,
                              std::unique_ptr<MessageBase> msg) {
      this->messageRouter(cl, std::move(msg));
    });
  }
};
}
