#pragma once
#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include "ActionProcessor.hpp"
#include "GameField.hpp"
#include "GameServer.hpp"
#include "LobbyServer.hpp"
#include "QuadTree.hpp"
#include "StateDumper.hpp"
#include "message.hpp"

namespace sfio {
class Node : public MessageProcessor {
  virtual void process(const ActionMessage *);
  virtual void process(const SpawnMessage *);
  virtual void process(const HandshakeMessage *);

  using Room = std::weak_ptr<GameField>;

  std::shared_ptr<GameServer> gameServer;  // This server is shared
                                           // between it's clients
  std::unique_ptr<LobbyServer> lobbyServer;
  std::unique_ptr<StateDumper> stateDumper;
  std::unique_ptr<ActionProcessor> actionProcessor;
  std::vector<Room> rooms;
  boost::posix_time::time_duration duration;
  boost::asio::deadline_timer timer;
  std::function<void(const boost::system::error_code &)> timerHander;

  GameField::Players players;

  void onTimer() {
    std::cout << "here 200 millis"
              << std::chrono::system_clock::now().time_since_epoch().count()
              << "\n";
  }
  void messageRouter(std::shared_ptr<GameServer::Client> cl,
                     std::unique_ptr<MessageBase> &&msg) {
    msg->process(this);
  };
  inline void findRoomForPlayer(std::shared_ptr<GameServer::Client>) noexcept;
  void clientDisconnected(std::shared_ptr<GameServer::Client>);

 public:
  Node(boost::asio::io_service &service, std::unique_ptr<GameServer> &&gs)
      : gameServer(std::move(gs)),
        duration(boost::posix_time::milliseconds(200)),
        timer(service, duration) {
    timerHander = [&](const boost::system::error_code &) {
      auto expires = timer.expires_at();
      timer.expires_at(expires + boost::posix_time::milliseconds(200));
      this->onTimer();
      timer.async_wait(timerHander);
    };
    timer.async_wait(timerHander);
    gameServer->onMessage([&](std::shared_ptr<GameServer::Client> cl,
                              std::unique_ptr<MessageBase> msg) {
      this->messageRouter(cl, std::move(msg));
    });
    gameServer->onDisconnect([&](std::shared_ptr<GameServer::Client> cl) {
      this->clientDisconnected(cl);
    });
  }
};
}
