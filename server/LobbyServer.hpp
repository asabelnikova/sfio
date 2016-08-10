#pragma once
#include <functional>

namespace sfio {
struct LobbyServer {
  typedef int Rooms;
  typedef int Clients;

  virtual void onConnect(std::function<void()>) = 0;
  virtual void sendLoad(Rooms, Clients) = 0;
  virtual ~LobbyServer(){};
};
}
