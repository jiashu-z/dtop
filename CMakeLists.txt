cmake_minimum_required(VERSION 3.19)
project(dtop-rpc)
include(common.cmake)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(pugixml REQUIRED)

add_subdirectory(proto)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(worker)
add_subdirectory(common)
add_subdirectory(vadaptor)
