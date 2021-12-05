#include "utils.hpp"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <memory>

namespace example {

zmq::message_t encodeMessage(const Message& msg) {
    constexpr auto buffer_size{sizeof(Message)};
    uint8_t output_buffer[buffer_size];

    google::protobuf::io::ArrayOutputStream raw_output(output_buffer,
                                                       buffer_size);
    google::protobuf::io::CodedOutputStream coded_output(&raw_output);

    std::string serialized_message;
    msg.SerializeToString(&serialized_message);

    coded_output.WriteVarint32(serialized_message.size());
    coded_output.WriteString(serialized_message);

    zmq::message_t encoded_message(buffer_size);
    std::memcpy(encoded_message.data(), output_buffer, buffer_size);
    return encoded_message;
}

Message decodeMessage(const zmq::message_t& msg) {
    Message decoded_message;

    google::protobuf::io::ArrayInputStream raw_input(msg.data(), msg.size());
    google::protobuf::io::CodedInputStream coded_input(&raw_input);

    std::string serialized_msg;
    uint32_t serialized_size;

    coded_input.ReadVarint32(&serialized_size);
    coded_input.ReadString(&serialized_msg, serialized_size);

    decoded_message.ParseFromString(serialized_msg);
    return decoded_message;
}
}  // namespace example