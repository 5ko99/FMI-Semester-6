cmake_minimum_required(VERSION 3.17)
project(testing)

set(CMAKE_CXX_STANDARD 20)

add_executable(testing tests/catch2/catch2.cpp tests/catch2/catch2.h factorial.cpp factorial.h tests/tests.cpp)