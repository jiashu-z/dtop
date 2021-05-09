cmake_minimum_required(VERSION 3.19)
project(client)

add_library(client SHARED
src/Client.cpp)
target_include_directories(client
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
)