#pragma once

#include <unordered_map>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "GameServer.hpp"
#include "PacketFactory.hpp"

namespace sfio {
class GameServerWS : public GameServer {
  typedef websocketpp::server<websocketpp::config::asio> server;
  boost::asio::io_service &io_service;
  std::unordered_map<uint64_t, Client> clientsConnected;
  server websocketServer;
  PacketFactory packetFactory;
  OnMessageCallback onMessage_;
  OnConnectCallback onConnect_;
  void sendMessage(const Client &, std::string &&) override;
  void onMessage(OnMessageCallback) override;
  void onConnect(OnConnectCallback) override;
  websocketpp::connection_hdl handler(const Client &);

 public:
  GameServerWS(boost::asio::io_service &s) : io_service(s) {
    websocketServer.init_asio(&s);
    websocketServer.set_reuse_addr(true);
    websocketServer.set_open_handler([&](websocketpp::connection_hdl hdl) {
      auto id = uint64_t(hdl.lock().get());
      clientsConnected[id] = std::move(createClient(id));
    });
    websocketServer.set_message_handler(
        [&](websocketpp::connection_hdl hdl, server::message_ptr msg) {
          auto &payload = msg->get_raw_payload();
          auto id = uint64_t(hdl.lock().get());
          if (onMessage_) {
            auto pkt = packetFactory.create(payload);
            pkt->client = &clientsConnected[id];
            onMessage_(clientsConnected[id], std::move(pkt));
          } else {
            std::cerr << "on message function in not installed\n";
          }
          std::cout << "Message recv \n";
        });
    websocketServer.listen(9002);
    websocketServer.start_accept();
  };
};
}
