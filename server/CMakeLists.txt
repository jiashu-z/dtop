cmake_minimum_required(VERSION 3.19)
project(server)

add_executable(server
src/main.cpp
src/Server.cpp
src/ConcreteGRPCService.cpp)

target_include_directories(server
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
PUBLIC ${CMAKE_SOURCE_DIR}/proto
PUBLIC "/home/zhangjiashu/.local/include"
)
target_link_directories(server
PUBLIC ${CMAKE_SOURCE_DIR}/build/proto
)
target_link_libraries(server
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF}
proto
)