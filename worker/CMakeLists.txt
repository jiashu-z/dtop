cmake_minimum_required(VERSION 3.19)
project(worker)

add_executable(worker
src/main.cpp
src/MemUsageWorker.cpp)

target_include_directories(worker
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(worker
PRIVATE proto)