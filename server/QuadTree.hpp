#pragma once
#include <array>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace sfio {

struct node {
  float size;
  std::array<float, 2> position;
  node(float, std::array<float, 2>);
};

class QuadTree {
  enum PART { NE, NW, SW, SE };
  const int maxSize = 100;
  std::unordered_map<uint64_t, node> nodes;
  std::vector<std::unique_ptr<QuadTree>> children;
  QuadTree *parent = nullptr;
  bool hasChildren = false;

  void split();
  void collapseChildren();
  void moveNodesToChildren();
  void moveNodesToParent();

  void set(uint64_t, node &&);
  void remove(uint64_t);
  void detectCollisions(std::function<void(node &, node &)>);

 public:
  uint32_t count();
};
}
