cmake_minimum_required(VERSION 3.21)

project(cpp_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
endif()

# Take care of conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include_directories(inc)

set(CPP_EX "CPP_EX")

set(CPP_EX_SRC
	src/client.cpp
	src/server.cpp
	)

set(CPP_EX_INC
	inc/client.hpp
	inc/server.hpp
	)

add_library(${CPP_EX} ${CPP_EX_SRC} ${CPP_EX_INC})
target_include_directories(${CPP_EX} PUBLIC inc)
target_link_libraries(${CPP_EX} CONAN_PKG::spdlog CONAN_PKG::cppzmq) 

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::cpptoml CONAN_PKG::cli11 CONAN_PKG::protobuf ${CPP_EX})