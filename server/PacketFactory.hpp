#pragma once
#include <memory>
#include <string>
#include "message.hpp"

namespace sfio {
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
