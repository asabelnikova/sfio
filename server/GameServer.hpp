#pragma once
#include <functional>
#include <memory>
#include "Client.hpp"

namespace sfio {

class MessageBase;
struct GameServer {
  class Client;

  typedef std::function<void(Client, std::unique_ptr<MessageBase>)>
      OnMessageCallback;
  typedef std::function<void(uint64_t, Client)> OnConnectCallback;
  virtual void onConnect(OnConnectCallback) = 0;
  virtual void onMessage(OnMessageCallback) = 0;
  virtual void sendMessage(const Client &, std::string &&) = 0;
  virtual ~GameServer(){};

 protected:
  Client createClient(uint64_t id) { return Client(this, id); }

 public:
  class Client {
    GameServer *serverInst;
    uint64_t id;
    Client(GameServer *s, uint64_t id) : serverInst(s), id(id){};
    friend Client GameServer::createClient(uint64_t);

   public:
    Client() = default;
    void send(std::string &&message) {
      serverInst->sendMessage(*this, std::forward<std::string>(message));
    }
    uint64_t getId() { return id; }
    uint64_t getId() const { return id; }
  };
};
}
