#include "server.hpp"

#include <thread>

#include "spdlog/spdlog.h"
#include "utils.hpp"

namespace example {
void runServer(std::string_view name, int port) {
    //  Prepare our context and socket
    zmq::context_t context(2);
    zmq::socket_t socket(context, zmq::socket_type::rep);
    socket.bind(fmt::format("tcp://*:{}", port));

    while (true) {
        zmq::message_t request;
        auto _{socket.recv(request, zmq::recv_flags::none)};
        const auto decoded_request{example::decodeMessage(request)};
        spdlog::info("Received request: {}, {}, {}, {}", decoded_request.id(),
                     decoded_request.source(), decoded_request.target(),
                     decoded_request.content());

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        Message reply;
        reply.set_content("OK");
        socket.send(example::encodeMessage(reply), zmq::send_flags::none);
    }
}
}  // namespace example