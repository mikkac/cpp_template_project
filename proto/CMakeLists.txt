set(PROTO_LIB "proto_lib")

set(PROTO_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/message.proto
)

protobuf_generate_cpp(PROTO_SRC PROTO_INC ${PROTO_FILES})
add_library(${PROTO_LIB} STATIC ${PROTO_SRC} ${PROTO_INC})
target_link_libraries(${PROTO_LIB} CONAN_PKG::protobuf)

target_include_directories(${PROTO_LIB} PUBLIC ${CMAKE_BINARY_DIR}/proto)