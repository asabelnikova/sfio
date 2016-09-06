#include "Player.hpp"
#include <glm/geometric.hpp>
#include <glm/vec2.hpp>
#include <iostream>

namespace sfio {

using v2Param = TypedParameter<glm::tvec2<double>>;
using sParam = TypedParameter<double>;

std::weak_ptr<GameServer::Client> Player::getClient() { return client; }
const Player::ParamMap& Player::getParameters() { return parameters; }
void Player::set(std::string s, std::unique_ptr<Parameter> ptr) {
  parameters[s] = std::move(ptr);
}

void Player::processAction(const ActionMessage* msg) {
  switch (msg->data.type()) {
    case gamemessages::Action_Type_Thrust: {
      sParam& massP = *dynamic_cast<sParam*>(parameters["mass"].get());
      sParam& thrustP = *dynamic_cast<sParam*>(parameters["thrust"].get());
      v2Param& positionP =
          *dynamic_cast<v2Param*>(parameters["position"].get());

      auto& position = positionP.data;
      auto& velocity = positionP.velocity;
      double mass = massP.data;
      double thrust = thrustP.data;
      double calculatedAt = positionP.calculatedAt;
      auto dt = (msg->data.startedon() - calculatedAt) / 1000.0f;
      glm::tvec2<double> onPoint(msg->data.onpoint().x(),
                                 msg->data.onpoint().y());
      auto dx = velocity * dt;
      auto dv =
          glm::normalize(onPoint - position) * (thrust / mass * msg->data.dt());
      position += dx;
      velocity += dv;
      positionP.calculatedAt = msg->data.startedon();
      std::cout << "dx " << position.x << " " << position.y << "\n";
    }

    default:
      return;
  }

  std::cout << "PROCESS PLAYER MESSAGE\n";
}
}
