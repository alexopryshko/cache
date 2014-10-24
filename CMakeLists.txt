cmake_minimum_required(VERSION 2.8.4)
project(cache)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCE_FILES main.cpp)
add_executable(cache ${SOURCE_FILES})