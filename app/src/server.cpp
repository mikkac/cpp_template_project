#include <unistd.h>

#include <iostream>
#include <thread>

#include "client.hpp"
#include "spdlog/spdlog.h"

// Taken from ZMQ docs examples
namespace example {
void runServer(std::string_view name, int port) {
    //  Prepare our context and socket
    zmq::context_t context(2);
    zmq::socket_t socket(context, zmq::socket_type::rep);
    socket.bind(fmt::format("tcp://*:{}", port));

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        auto _{socket.recv(request, zmq::recv_flags::none)};
        spdlog::info(
            "Received request: {}",
            std::string(static_cast<char*>(request.data()), request.size()));
        //  Do some 'work'
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        //  Send reply back to client
        std::string reply_str{"reply"};
        zmq::message_t reply(reply_str.length());
        memcpy(reply.data(), reply_str.data(), reply_str.length());
        socket.send(reply, zmq::send_flags::none);
        spdlog::info("Sending reply: {}", reply_str);
    }
}
}  // namespace example