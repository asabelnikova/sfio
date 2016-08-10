#include "GameServerWS.hpp"

namespace sfio {
void GameServerWS::onMessage(OnMessageCallback cb) { onMessage_ = cb; }
void GameServerWS::onConnect(OnConnectCallback cb) { onConnect_ = cb; }
void GameServerWS::sendMessage(const MessageBase* msg) {}
}
