#pragma once
#include <websocketpp/config/asio.hpp>
#include <websocketpp/server.hpp>
#include "GameServer.hpp"

namespace sfio {
class GameServerWS : public GameServer {
  typedef websocketpp::server<websocketpp::config::asio> server;
  boost::asio::io_service &io_service;
  server websocketServer;
  OnMessageCallback onMessage_;
  OnConnectCallback onConnect_;
  void sendMessage(const MessageBase *) override;
  void onMessage(OnMessageCallback) override;
  void onConnect(OnConnectCallback) override;

 public:
  GameServerWS(boost::asio::io_service &s) : io_service(s) {
    websocketServer.init_asio(&s);
    websocketServer.set_reuse_addr(true);
    websocketServer.set_open_handler([&](websocketpp::connection_hdl hdl) {
      std::cout << "Connecttion establisehd"
                << "\n";
    });
    websocketServer.set_message_handler(
        [&](websocketpp::connection_hdl hdl, server::message_ptr msg) {
          std::cout << "Message recv \n";

        });
    websocketServer.listen(9002);
    websocketServer.start_accept();
  };
};
}
