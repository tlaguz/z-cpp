cmake_minimum_required(VERSION 3.9)
project(zajecia3)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)

add_executable(zajecia3 main.cpp zespolona.hpp wykonywacz.hpp)