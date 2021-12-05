#define CATCH_CONFIG_MAIN
#include "utils.hpp"

#include <catch2/catch.hpp>

#include "spdlog/spdlog.h"

TEST_CASE("Message proto is encoded and decoded properly") {
    Message message;
    constexpr int32_t msg_id{12};
    const std::string msg_source{"source"};
    const std::string msg_target{"target"};
    const std::string msg_content{"content"};

    message.set_id(msg_id);
    message.set_source(msg_source);
    message.set_target(msg_target);
    message.set_content(msg_content);

    const auto encoded_message{example::encodeMessage(message)};
    const auto decoded_message{example::decodeMessage(encoded_message)};

    REQUIRE(decoded_message.id() == msg_id);
    REQUIRE(decoded_message.source() == msg_source);
    REQUIRE(decoded_message.target() == msg_target);
    REQUIRE(decoded_message.content() == msg_content);
}