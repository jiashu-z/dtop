cmake_minimum_required(VERSION 3.19)
project(proto)

include(${CMAKE_SOURCE_DIR}/common.cmake)

set(PROTO_FILES hello.proto)

add_library(proto SHARED
${PROTO_FILES})

target_include_directories(proto
PRIVATE proto)

target_link_libraries(proto
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF})

protobuf_generate(TARGET proto
LANGUAGE cpp
GENERATE_EXTENSIONS .pb.h .pb.cc
PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}
PLUGIN "protoc-gen-cpp=/home/zhangjiashu/env/bin/protoc-gen-cpp"
)
protobuf_generate(TARGET proto
LANGUAGE grpc 
GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}
PLUGIN "protoc-gen-grpc=/home/zhangjiashu/env/bin/protoc-gen-grpc"
)
