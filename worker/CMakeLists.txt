cmake_minimum_required(VERSION 3.19)
project(worker)

add_library(worker SHARED
src/BaseWorker.cpp
src/ProfileQuery.cpp
src/Manager.cpp
src/MemUsageWorker.cpp
)

target_include_directories(worker
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
PUBLIC ${CMAKE_SOURCE_DIR}/proto
)

target_link_libraries(worker
PRIVATE proto)