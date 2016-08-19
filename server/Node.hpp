#pragma once
#include <iostream>
#include <memory>
#include "Client.hpp"
#include "GameServer.hpp"
#include "LobbyServer.hpp"
#include "Player.hpp"
#include "QuadTree.hpp"
#include "StateDumper.hpp"
#include "message.hpp"

namespace sfio {
class Node : public MessageProcessor {
  const int MAX_COUNT_PER_ROOM = 500;
  virtual void process(const ThrustMessage *) { std::cout << " TH MES\n"; };
  virtual void process(const SpawnMessage *);
  virtual void process(const HandshakeMessage *);
  virtual void process(const ShootMessage *) { std::cout << "SSS MES\n"; };

  typedef std::unique_ptr<QuadTree> Room;  // shared between node and players;
  std::unique_ptr<GameServer> gameServer;
  std::unique_ptr<LobbyServer> lobbyServer;
  std::unique_ptr<StateDumper> stateDumper;
  std::vector<Room> rooms;
  std::vector<Player> players;

  void messageRouter(GameServer::Client cl,
                     std::unique_ptr<MessageBase> &&msg) {
    msg->process(this);
  };

 public:
  Node(std::unique_ptr<GameServer> &&gs) : gameServer(std::move(gs)) {
    gameServer->onMessage(
        [&](GameServer::Client cl, std::unique_ptr<MessageBase> msg) {
          this->messageRouter(cl, std::move(msg));
        });
  }
};
}
