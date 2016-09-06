#pragma once
#include <memory>
#include <string>
#include "message.hpp"

namespace gamemessages {
class Parameter;
}

namespace sfio {

using ParameterPtr = std::unique_ptr<gamemessages::Parameter>;

template <typename T>
ParameterPtr createParameter(T data, T velocity, double calculatedAt);

class PacketFactory {
  class incoming_packet_not_parsed_error : public std::exception {
    virtual const char *what() const throw() {
      return "Could not parse incoming packet";
    }
  } not_parsed;

 public:
  std::unique_ptr<MessageBase> create(const std::string &);
};
}
