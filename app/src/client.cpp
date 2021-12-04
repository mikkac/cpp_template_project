#include "client.hpp"

#include <unistd.h>

#include <iostream>
#include <thread>

#include "spdlog/spdlog.h"

#include "message.pb.h"

// Taken from ZMQ docs examples
namespace example {
void runClient(std::string_view name, int port) {
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::req);
    spdlog::info("{} is connecting to server", name);
    socket.connect(fmt::format("tcp://localhost:{}", port));

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr < 50; request_nbr++) {
        auto request_str{fmt::format("msg_{}", request_nbr)};
        zmq::message_t request(request_str.length());
        memcpy(request.data(), request_str.data(), request_str.length());
        spdlog::info("Sending request {}: {}", request_nbr, request_str);
        socket.send(request, zmq::send_flags::none);

        //  Get the reply.
        zmq::message_t reply;
        auto _{socket.recv(reply, zmq::recv_flags::none)};
        spdlog::info(
            "{} received reply: {}", name,
            std::string(static_cast<char*>(reply.data()), reply.size()));
    }
}
}  // namespace example