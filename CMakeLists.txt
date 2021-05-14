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

# add_executable(demo_grpc main.cpp ConcreteObjService.cpp proto/hello.pb.cc proto/hello.grpc.pb.cc)
# target_include_directories(demo_grpc
#         PRIVATE proto)
# target_link_libraries(demo_grpc
#         ${_REFLECTION}
#         ${_GRPC_GRPCPP}
#         ${_PROTOBUF_LIBPROTOBUF})

# add_executable(client client.cpp ConcreteObjService.cpp proto/hello.pb.cc proto/hello.grpc.pb.cc)
# target_include_directories(client
#         PRIVATE proto)
# target_link_libraries(client
#         ${_REFLECTION}
#         ${_GRPC_GRPCPP}
#         ${_PROTOBUF_LIBPROTOBUF})

