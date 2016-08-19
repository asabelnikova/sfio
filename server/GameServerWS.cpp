#include "GameServerWS.hpp"

namespace sfio {
websocketpp::connection_hdl GameServerWS::handler(const Client &cl) {
  server::connection_type *con = (server::connection_type *)cl.getId();
  return websocketpp::connection_hdl(con->shared_from_this());
}
void GameServerWS::onMessage(OnMessageCallback cb) { onMessage_ = cb; }
void GameServerWS::onConnect(OnConnectCallback cb) { onConnect_ = cb; }
void GameServerWS::sendMessage(const Client &client, std::string &&message) {
  try {
    websocketServer.send(handler(client), message,
                         websocketpp::frame::opcode::BINARY);
  } catch (websocketpp::exception &e) {
    std::cerr << "[ERROR] " << e.what() << std::endl;
  }
}
}
