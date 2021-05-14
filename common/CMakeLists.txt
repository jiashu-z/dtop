cmake_minimum_required(VERSION 3.19)
project(common)

add_library(common SHARED
src/LibXML.cpp
src/LibNet.cpp
src/LibMath.cpp)
target_include_directories(common
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
