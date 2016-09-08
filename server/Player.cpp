#include "Player.hpp"
#include <glm/geometric.hpp>
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

std::vector<glm::tvec2<double>> Player::getGravityAccelerations(
    glm::dvec2 inPosition) {
  double mass = 50000000 * 1.1;
  double G = 6.67e-11;
  double mu = mass * G;
  glm::dvec2 center(0.0, 0.35);
  auto r = center - inPosition;
  auto F = mu / (glm::length(r) * glm::length(r));
  auto acc = glm::normalize(r) * F;
  std::cout << "acc " << acc.x << " " << acc.y << "\n";
  return {acc};
}

Player::state Player::calculatePositionWithForces(
    const Player::state& st, double timeLeftSincePosition) {
  auto dx = st.velocity * timeLeftSincePosition;
  state finalState = st;
  while (timeLeftSincePosition > timeStep) {
    std::cout << "=== time to calculate " << timeLeftSincePosition << " "
              << "\n";
    finalState = calculateNewState(finalState, timeStep, glm::dvec2(0));
    timeLeftSincePosition -= timeStep;
  }
  finalState =
      calculateNewState(finalState, timeLeftSincePosition, glm::dvec2(0));
  return finalState;
}

void Player::calculateLastState(double timestamp) {
  v2Param& positionP = *dynamic_cast<v2Param*>(parameters["position"].get());
  auto& initialPosition = positionP.data;
  auto& velocity = positionP.velocity;
  double calculatedAt = positionP.calculatedAt;

  auto prevousState = state{initialPosition, velocity};
  std::cout << "initial velocity: " << velocity.x << " " << velocity.y << "\n";

  auto dtLinear = (timestamp - calculatedAt) / 1000.0f;
  auto newState = calculatePositionWithForces(prevousState, dtLinear);
  positionP.data = newState.position;
  positionP.velocity = newState.velocity;
  positionP.calculatedAt = timestamp;
  std::cout << "position " << newState.position.x << " " << newState.position.y
            << "\n";
  std::cout << "velocity " << newState.velocity.x << " " << newState.velocity.y
            << "\n";
}
void Player::processAction(const ActionMessage* msg) {
  switch (msg->data.type()) {
    case gamemessages::Action_Type_Thrust: {
      sParam& massP = *dynamic_cast<sParam*>(parameters["mass"].get());
      sParam& thrustP = *dynamic_cast<sParam*>(parameters["thrust"].get());
      v2Param& positionP =
          *dynamic_cast<v2Param*>(parameters["position"].get());

      auto& initialPosition = positionP.data;
      auto& velocity = positionP.velocity;
      double mass = massP.data;
      double thrust = thrustP.data;
      double calculatedAt = positionP.calculatedAt;

      auto prevousState = state{initialPosition, velocity};

      auto dtLinear = (msg->data.startedon() - calculatedAt) / 1000.0f;
      auto initialState = calculatePositionWithForces(prevousState, dtLinear);

      double dt = msg->data.dt();
      glm::tvec2<double> onPoint(msg->data.onpoint().x(),
                                 msg->data.onpoint().y());

      auto dxa = velocity * dt;
      std::cout << std::setprecision(15);
      auto a =
          glm::normalize(onPoint - initialState.position) * (thrust / mass);
      auto newState = calculateNewState(initialState, dt, a);

      positionP.data = newState.position;
      positionP.velocity = newState.velocity;

      positionP.calculatedAt = msg->data.startedon() + msg->data.dt() * 1000.0;
    }

    default:
      return;
  }
}
}
