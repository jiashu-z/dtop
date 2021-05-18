cmake_minimum_required(VERSION 3.19)
project(server)

add_executable(server
src/main.cpp
src/Server.cpp
src/ConcreteGRPCService.cpp
src/ServerProperty.cpp)

target_include_directories(server
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
PUBLIC ${CMAKE_SOURCE_DIR}/proto
PUBLIC "/home/zjs/.local/include"
PUBLIC "/home/zhangjiashu/.local/include"
PUBLIC ${CMAKE_SOURCE_DIR}/common/inc
PUBLIC "/include"
PUBLIC ${CMAKE_SOURCE_DIR}/worker/inc
PUBLIC ${CMAKE_SOURCE_DIR}/client/inc
)
target_link_directories(server
PUBLIC ${CMAKE_SOURCE_DIR}/cmake-build-debug/proto
PUBLIC ${CMAKE_SOURCE_DIR}/cmake-build-debug/worker
PUBLIC ${CMAKE_SOURCE_DIR}/cmake-build-debug/client
)
target_link_libraries(server
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF}
proto
worker
common
pugixml
client
)

