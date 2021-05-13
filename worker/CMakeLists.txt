cmake_minimum_required(VERSION 3.19)
project(worker)

add_library(worker SHARED
inc/BaseWorker.hpp
src/MemUsageWorker.cpp
src/ProfileQuery.cpp)

target_include_directories(worker
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
PUBLIC ${CMAKE_SOURCE_DIR}/proto
)

target_link_libraries(worker
PRIVATE proto)