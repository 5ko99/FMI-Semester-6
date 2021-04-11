cmake_minimum_required(VERSION 3.19)
project(8Puzzle)

set(CMAKE_CXX_STANDARD 20)

include_directories("Headers","Source")

add_executable(8Puzzle main.cpp Source/State.cpp Headers/State.h Source/Node.cpp Headers/Node.h Source/CompareFunctorForBestFirst.cpp Headers/CompareFunctorForBestFirst.h Source/CompareFunctorForAStar.cpp Headers/CompareFunctorForAStar.h Source/Solver.cpp Headers/Solver.h)