cmake_minimum_required(VERSION 3.19)
project(client)

add_library(client SHARED
src/Client.cpp
src/ConcreteGRPCServiceClient.cpp)
target_include_directories(client
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
PUBLIC ${CMAKE_SOURCE_DIR}/proto
PUBLIC "/home/zhangjiashu/.local/include"
PUBLIC "/include"
)
target_include_directories(client
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc
)