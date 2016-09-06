#pragma once
#include "PacketFactory.hpp"

namespace sfio {
struct Parameter {
  virtual std::unique_ptr<gamemessages::Parameter> serialize() = 0;
  virtual ~Parameter(){};
};

template <typename T>
struct TypedParameter : public Parameter {
  T data, velocity;
  double calculatedAt;
  std::unique_ptr<gamemessages::Parameter> serialize() {
    return std::move(createParameter(data, velocity, calculatedAt));
  }
  TypedParameter(T& d, T& v, double c)
      : data(std::forward<T>(d)),
        velocity(std::forward<T>(v)),
        calculatedAt(c) {}
  TypedParameter(T&& d, T&& v, double c)
      : data(std::forward<T>(d)),
        velocity(std::forward<T>(v)),
        calculatedAt(c) {}
};
}
