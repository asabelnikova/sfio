#pragma once
#include <array>
#include <functional>
namespace sfio {

template <typename Ix, typename N>
struct GeoSpacialIndex {
  virtual void set(Ix, N &&) = 0;
  virtual void remove(Ix) = 0;
  virtual void detectCollisions(std::function<void(N &, N &)>) = 0;
  virtual ~GeoSpacialIndex(){};
};
}
