#include "message.hpp"
namespace sfio {
struct ActionProcessor {
  virtual void process(const ActionMessage *message) = 0;
  virtual ~ActionProcessor(){};
};
}
