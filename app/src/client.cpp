#include "client.hpp"

#include <thread>

#include "spdlog/spdlog.h"
#include "utils.hpp"

namespace example {
void runClient(std::string_view name, int port) {
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::req);
    spdlog::info("{} is connecting to server", name);
    socket.connect(fmt::format("tcp://localhost:{}", port));

    Message msg;
    for (int req_num = 0; req_num < 50; req_num++) {
        msg.set_id(req_num);
        msg.set_source(std::string(name));
        msg.set_target("target_server");
        msg.set_content(fmt::format("msg_{}", req_num));
        auto msg_to_send{example::encodeMessage(msg)};
        socket.send(msg_to_send, zmq::send_flags::none);

        zmq::message_t reply;
        auto _{socket.recv(reply, zmq::recv_flags::none)};
        const auto reply_msg{example::decodeMessage(reply)};
        spdlog::info("{} received reply: {}", name, reply_msg.content());
    }
}
}  // namespace example