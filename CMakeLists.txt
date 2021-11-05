cmake_minimum_required(VERSION 3.20)
project(gnnt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -O3")
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts-diagnostics-depth=3")
endif()

include_directories(include)
add_executable(main main.cpp)
