include_directories(inc)

set(CPP_EX_LIB "cpp_ex_lib")

set(CPP_EX_LIB_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
)

set(CPP_EX_LIB_INC
	${CMAKE_CURRENT_SOURCE_DIR}/inc/client.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/inc/server.hpp
)

add_library(${CPP_EX_LIB} ${CPP_EX_LIB_SRC} ${CPP_EX_LIB_INC})
target_include_directories(${CPP_EX_LIB} PUBLIC inc ${CMAKE_BINARY_DIR}/proto)
target_link_libraries(${CPP_EX_LIB} CONAN_PKG::spdlog CONAN_PKG::cppzmq CONAN_PKG::protobuf ${PROTO_LIB}) 

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::cpptoml CONAN_PKG::cli11 ${CPP_EX_LIB})