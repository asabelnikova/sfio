#include <boost/asio.hpp>
#include "GameServerWS.hpp"
#include "Node.hpp"

using namespace sfio;
int main() {
  boost::asio::io_service service;

  GameServerWS server(service);
  Node node;
  service.run();
}
