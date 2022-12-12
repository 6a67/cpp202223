cmake_minimum_required(VERSION 3.25)
project(uebung08)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(uebung08
        List.hpp
        List.tcc
        ListTest.cpp)
