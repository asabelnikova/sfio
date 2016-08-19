#include "QuadTree.hpp"
#include <algorithm>
namespace sfio {
uint32_t QuadTree::count() {
  uint32_t t = 0;
  std::for_each(children.begin(), children.end(),
                [&t](auto &item) { t += item->count(); });
  return t + nodes.size();
}
}
