include_directories(inc)

set(CPP_EX_LIB_SRC
${CMAKE_CURRENT_SOURCE_DIR}/src/configparser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
)

set(CPP_EX_LIB_INC
${CMAKE_CURRENT_SOURCE_DIR}/inc/configparser.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/inc/client.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/inc/server.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/inc/utils.hpp
)

add_library(${CPP_EX_LIB} ${CPP_EX_LIB_SRC} ${CPP_EX_LIB_INC})
target_include_directories(${CPP_EX_LIB} PUBLIC inc ${CMAKE_BINARY_DIR}/proto)
target_link_libraries(${CPP_EX_LIB} CONAN_PKG::cli11 CONAN_PKG::tomlplusplus CONAN_PKG::spdlog CONAN_PKG::cppzmq CONAN_PKG::protobuf ${PROTO_LIB}) 

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${CPP_EX_LIB})