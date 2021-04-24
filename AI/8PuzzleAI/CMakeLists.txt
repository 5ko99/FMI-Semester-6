cmake_minimum_required(VERSION 3.19)
project(8PuzzleAI)

set(CMAKE_CXX_STANDARD 20)

include_directories(Header
        Source)

add_executable(8PuzzleAI main.cpp
        Source/State.cpp
        Header/State.h
        Source/Node.cpp
        Header/Node.h
        Source/CompareFunctorForBestFirst.cpp
        Header/CompareFunctorForBestFirst.h
        Source/CompareFunctorForAStar.cpp
        Header/CompareFunctorForAStar.h
        Source/Solver.cpp
        Header/Solver.h)

