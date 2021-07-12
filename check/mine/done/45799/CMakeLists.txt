cmake_minimum_required(VERSION 3.19)
project(45799)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(45799
        Component.cpp
        Component.h
        Configuration.cpp
        Configuration.h
        Cpu.cpp
        Cpu.h
        main.cpp
        Memory.cpp
        Memory.h
        Utils.cpp)
