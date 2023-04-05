cmake_minimum_required(VERSION 3.24)
project(LaminarFlow)

find_package(tinyxml2 CONFIG REQUIRED)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

add_executable(LaminarFlow main.cpp src/data.hpp src/laminarflow.hpp src/logger.hpp)
target_link_libraries(LaminarFlow tinyxml2::tinyxml2)