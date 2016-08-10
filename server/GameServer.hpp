#pragma once
#include <functional>
#include "Client.hpp"
#include "message.hpp"

namespace sfio {
struct GameServer {
  typedef std::function<void(Client, std::unique_ptr<MessageBase>)>
      OnMessageCallback;
  typedef std::function<void(uint64_t, Client)> OnConnectCallback;
  virtual void onConnect(OnConnectCallback) = 0;
  virtual void onMessage(OnMessageCallback) = 0;
  virtual void sendMessage(const MessageBase*) = 0;
  virtual ~GameServer(){};
};
}
