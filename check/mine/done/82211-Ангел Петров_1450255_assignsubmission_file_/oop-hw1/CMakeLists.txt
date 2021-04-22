cmake_minimum_required(VERSION 3.19)
project(oop_hw1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(oop_hw1
        garage.cpp
        garage.h
        main.cpp
        mystring.cpp
        myString.h
        utils.cpp
        utils.h
        vehicle.cpp
        vehicle.h
        vehicleAllocator.cpp
        vehicleAllocator.h)
