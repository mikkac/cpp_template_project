#pragma once

#include "message.pb.h"
#include "zmq.hpp"

namespace example {

zmq::message_t encodeMessage(const Message& msg);

Message decodeMessage(const zmq::message_t& msg);
}  // namespace example