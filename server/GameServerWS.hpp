#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "GameServer.hpp"
#include "PacketFactory.hpp"

namespace sfio {
class GameServerWS : public GameServer {
  typedef websocketpp::server<websocketpp::config::asio> server;
  boost::asio::io_service &io_service;
  ClientStorage clientsConnected;
  server websocketServer;
  PacketFactory packetFactory;
  OnMessageCallback onMessage_;
  OnConnectCallback onConnect_;
  void sendToAllBut(std::shared_ptr<Client>, std::string &&) override;
  void sendMessage(std::shared_ptr<Client>, std::string &&) override;
  void onMessage(OnMessageCallback) override;
  void onConnect(OnConnectCallback) override;
  inline websocketpp::connection_hdl handler(std::shared_ptr<Client>) const;

 public:
  GameServerWS(boost::asio::io_service &s);
};
}
