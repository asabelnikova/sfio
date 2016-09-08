#pragma once
#include <glm/vec2.hpp>
#include <memory>
#include "GameServer.hpp"
#include "Parameter.hpp"
#include "message.hpp"

namespace sfio {
class GameField;

struct RungeKutta {};

class Player {
  const double timeStep = 0.015;
  struct derivative {
    glm::dvec2 velocity, acceleration;
  };
  struct state {
    glm::dvec2 position, velocity;
  };
  derivative initWithThrustAcceleration(
      const state &st, glm::dvec2 positionIndependentAcceleration) {
    auto gravityAccelerationsAtPoint = getGravityAccelerations(st.position);
    for (auto &a : gravityAccelerationsAtPoint)
      positionIndependentAcceleration += a;
    return derivative{st.velocity, positionIndependentAcceleration};
  }
  derivative moveTowards(const state &fromState,
                         const derivative &prevDerivative, glm::dvec2 thrust,
                         double timeDelta) {
    auto p = fromState.position + prevDerivative.velocity * timeDelta;
    auto v = fromState.velocity + prevDerivative.acceleration * timeDelta;
    for (auto &a : getGravityAccelerations(p)) thrust += a;
    return derivative{v, thrust};
  }

  state calculateNewState(const state &fromState, double timeDelta,
                          glm::dvec2 positionIndependentAcceleration) {
    auto a =
        initWithThrustAcceleration(fromState, positionIndependentAcceleration);
    auto b = moveTowards(fromState, a, positionIndependentAcceleration,
                         timeDelta / 2.0);
    auto c = moveTowards(fromState, b, positionIndependentAcceleration,
                         timeDelta / 2.0);
    auto d =
        moveTowards(fromState, c, positionIndependentAcceleration, timeDelta);
    auto velocity =
        (a.velocity + (b.velocity + c.velocity) * 2.0 + d.velocity) / 6.0;
    auto acceleration =
        (a.acceleration + (b.acceleration + c.acceleration) * 2.0 +
         d.acceleration) /
        6.0;
    return state{fromState.position + velocity * timeDelta,
                 fromState.velocity + acceleration * timeDelta};
  }

 public:
  using ParamMap = std::unordered_map<std::string, std::unique_ptr<Parameter>>;

 private:
  std::weak_ptr<GameServer::Client> client;
  std::shared_ptr<GameField> room;
  ParamMap parameters;
  state calculatePositionWithForces(const state &st,
                                    double timeLeftSincePosition);

  std::vector<glm::tvec2<double>> getGravityAccelerations(
      glm::dvec2 inPosition);

 public:
  void processAction(const ActionMessage *);
  void calculateLastState(double timestamp);
  void set(std::string, std::unique_ptr<Parameter> p);
  std::weak_ptr<GameServer::Client> getClient();
  const ParamMap &getParameters();
  Player(std::weak_ptr<GameServer::Client> cl, std::shared_ptr<GameField> room)
      : client(cl), room(room) {}
};
}
