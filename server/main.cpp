#include <boost/asio.hpp>
#include "GameServerWS.hpp"
#include "Node.hpp"

using namespace sfio;
int main() {
  boost::asio::io_service service;

  // dynamic_cast<GameServer*>(&server)->onMessage(
  //[](GameServer::Client, std::unique_ptr<MessageBase> message) {
  // std::cout << "AAlalal\n";
  //});
  Node node(service, std::unique_ptr<GameServer>(new GameServerWS(service)));
  service.run();
}
