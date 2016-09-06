#include "StateDumper.hpp"
#include <chrono>
#include <iostream>
#include "GameField.hpp"
#include "gamemessage.pb.h"

namespace sfio {
using D = std::chrono::duration<double, std::ratio<1>>;
void StateDumper::dumpState(std::vector<std::weak_ptr<GameField>> &fields) {
  double timestamp = std::chrono::duration_cast<D>(
                         std::chrono::system_clock::now().time_since_epoch())
                         .count();
  for (auto &gameField : fields) {
    auto gfptr = gameField.lock();
    if (gfptr) gfptr->updateParameters(timestamp);
    gamemessages::OutcomingMessage outMessage;
    outMessage.set_type(gamemessages::OutcomingMessage::Scene);
    auto objects = outMessage.mutable_scene()->mutable_objects();
    std::cout << "WE HAVE " << gfptr->getPlayers().size() << "\n";
    for (auto &p : gfptr->getPlayers()) {
      auto obj = objects->Add();
      for (auto &param : p.second->getParameters()) {
        (*obj->mutable_parameters())[param.first] = *param.second->serialize();
      }
    }
    for (auto &p : gfptr->getPlayers()) {
      auto clientPtr = p.second->getClient().lock();
      if (clientPtr) clientPtr->send(outMessage.SerializeAsString());
    }
  }
}
}
