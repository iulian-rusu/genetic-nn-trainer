cmake_minimum_required(VERSION 3.20)
project(genetic_nn_trainer)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)

add_executable(genetic_nn_trainer main.cpp)
