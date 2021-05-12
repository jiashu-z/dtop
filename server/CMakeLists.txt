cmake_minimum_required(VERSION 3.19)
project(server)

add_executable(server
src/main.cpp
src/server.cpp)

target_include_directories(server
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
)