#pragma once
#include "Client.hpp"

namespace sfio {
class QuadTree;
class Player {
  Client *client;
  const QuadTree *room;
};
}
