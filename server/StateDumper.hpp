#pragma once
#include "Player.hpp"

namespace sfio{
struct StateDumper {
  virtual void dumpState(std::vector<Player>&) = 0;
  virtual ~StateDumper(){};
};
}
