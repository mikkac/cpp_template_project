#pragma once

#include <string>

#include "zmq.hpp"

namespace example {
void runServer(std::string_view name, int port);
}  // namespace example