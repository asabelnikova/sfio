#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include "Client.hpp"

namespace sfio {

class MessageBase;
struct GameServer : public std::enable_shared_from_this<GameServer> {
  class Client;

  using OnMessageCallback = std::function<void(std::shared_ptr<Client>,
                                               std::unique_ptr<MessageBase>)>;
  using OnDisconnectCallback = std::function<void(std::shared_ptr<Client>)>;
  using OnConnectCallback =
      std::function<void(uint64_t, std::shared_ptr<Client>)>;
  using ClientStorage = std::unordered_map<uint64_t, std::shared_ptr<Client>>;

  virtual void onConnect(OnConnectCallback) = 0;
  virtual void onDisconnect(OnDisconnectCallback) = 0;
  virtual void onMessage(OnMessageCallback) = 0;
  virtual void sendMessage(std::shared_ptr<Client>, std::string &&) = 0;
  virtual void sendToAllBut(std::shared_ptr<Client>, std::string &&) = 0;
  virtual ~GameServer(){};

 protected:
  std::shared_ptr<Client> createClient(uint64_t id) {
    return std::shared_ptr<Client>(new Client(shared_from_this(), id));
  }

 public:
  class Client : public std::enable_shared_from_this<Client> {
    std::shared_ptr<GameServer> serverInst;
    uint64_t id;
    Client(std::shared_ptr<GameServer> s, uint64_t id)
        : serverInst(s), id(id){};
    friend std::shared_ptr<Client> GameServer::createClient(uint64_t);

   public:
    Client() = default;
    void send(std::string &&message) {
      serverInst->sendMessage(shared_from_this(),
                              std::forward<std::string>(message));
    }
    uint64_t getId() { return id; }
    uint64_t getId() const { return id; }
  };
};
}
