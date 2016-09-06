#include "PacketFactory.hpp"
#include <glm/vec2.hpp>
#include "gamemessage.pb.h"
namespace sfio {
using V2 = glm::tvec2<double>;
using S = double;

template <>
ParameterPtr createParameter<V2>(V2 data, V2 velocity, double calculatedAt) {
  auto p = std::make_unique<gamemessages::Parameter>();
  p->mutable_vec2()->mutable_v()->set_x(data.x);
  p->mutable_vec2()->mutable_v()->set_y(data.y);
  p->mutable_vec2()->mutable_dv()->set_x(data.x);
  p->mutable_vec2()->mutable_dv()->set_y(data.y);
  p->set_calculatedat(calculatedAt);
  return std::move(p);
}
template <>
ParameterPtr createParameter<S>(S data, S velocity, double calculatedAt) {
  auto p = std::make_unique<gamemessages::Parameter>();
  p->mutable_scalar()->set_v(data);
  p->mutable_scalar()->set_dv(velocity);
  p->set_calculatedat(calculatedAt);
  return std::move(p);
}
}
