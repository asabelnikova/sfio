#include "GameServerWS.hpp"

namespace sfio {

GameServerWS::GameServerWS(boost::asio::io_service &s) : io_service(s) {
  websocketServer.init_asio(&s);
  websocketServer.set_reuse_addr(true);
  websocketServer.set_open_handler([&](websocketpp::connection_hdl hdl) {
    auto id = uint64_t(hdl.lock().get());
    clientsConnected[id] = createClient(id);
  });
  websocketServer.set_close_handler([&](websocketpp::connection_hdl hdl) {
    auto id = uint64_t(hdl.lock().get());
    onDisconnect_(clientsConnected[id]);
    clientsConnected.erase(id);
  });
  websocketServer.set_message_handler(
      [&](websocketpp::connection_hdl hdl, server::message_ptr msg) {
        auto &payload = msg->get_raw_payload();
        auto id = uint64_t(hdl.lock().get());
        if (onMessage_) {
          auto pkt = packetFactory.create(payload);
          pkt->client = clientsConnected[id];
          onMessage_(clientsConnected[id], std::move(pkt));
        } else {
          std::cerr << "on message function in not installed\n";
        }
        std::cout << "Message recv \n";
      });
  websocketServer.listen(9002);
  websocketServer.start_accept();
}

inline websocketpp::connection_hdl GameServerWS::handler(
    std::shared_ptr<Client> cl) const {
  server::connection_type *con = (server::connection_type *)cl->getId();
  return websocketpp::connection_hdl(con->shared_from_this());
}
void GameServerWS::onMessage(OnMessageCallback cb) { onMessage_ = cb; }
void GameServerWS::onConnect(OnConnectCallback cb) { onConnect_ = cb; }
void GameServerWS::onDisconnect(OnDisconnectCallback cb) { onDisconnect_ = cb; }
void GameServerWS::sendToAllBut(std::shared_ptr<Client> client,
                                std::string &&message) {
  std::cout << "message " << message.size() << "\n";
  for (auto &cl : clientsConnected) {
    if (cl.second->getId() != client->getId())
      sendMessage(cl.second, std::move(message));
  }
}
void GameServerWS::sendMessage(std::shared_ptr<Client> client,
                               std::string &&message) {
  try {
    websocketServer.send(handler(client), message,
                         websocketpp::frame::opcode::BINARY);
  } catch (websocketpp::exception &e) {
    std::cerr << "[ERROR] " << e.what() << std::endl;
  }
}
}
