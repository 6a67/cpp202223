cmake_minimum_required(VERSION 3.0.2)

project(gdb_linked_list)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -msse3 -Wno-deprecated-declarations -Wno-unused -Wcpp")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

add_executable(gdb_linked_list gdb.cpp)