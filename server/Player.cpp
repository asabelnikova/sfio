#include "Player.hpp"
#include <glm/geometric.hpp>
#include <glm/vec2.hpp>
#include <iomanip>
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

      auto dtLinear = (msg->data.startedon() - calculatedAt) / 1000.0f;

      double dt = msg->data.dt();
      glm::tvec2<double> onPoint(msg->data.onpoint().x(),
                                 msg->data.onpoint().y());

      auto dx = velocity * dtLinear;
      auto dxa = velocity * dt;
      std::cout << std::setprecision(15);
      auto a = glm::normalize(onPoint - position) * (thrust / mass);
      auto at = a * dt;
      auto at2 = a * dt * dt * 0.5;
      position += at2 + dx + dxa;
      velocity += at;

      positionP.calculatedAt = msg->data.startedon() + msg->data.dt() * 1000.0;
    }

    default:
      return;
  }
}
}
