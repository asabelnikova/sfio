#pragma once
#include "Player.hpp"

namespace sfio {
struct StateDumper {
  virtual void dumpState(std::vector<std::weak_ptr<GameField>>&);
  virtual ~StateDumper(){};
};
}
