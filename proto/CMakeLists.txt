set(PROTO_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/message.proto
)

protobuf_generate_cpp(PROTO_SRC PROTO_INC ${PROTO_FILES})
add_library(${PROTO_LIB} ${PROTO_INC} ${PROTO_SRC})
target_link_libraries(${PROTO_LIB} CONAN_PKG::protobuf)
target_include_directories(${PROTO_LIB} PUBLIC ${CMAKE_BINARY_DIR}/proto)