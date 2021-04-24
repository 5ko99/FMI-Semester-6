cmake_minimum_required(VERSION 3.19)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(src
        Garage.cpp
        Garage.h
        main.cpp
        MyString.cpp
        MyString.h
        Vehicle.cpp
        Vehicle.h
        VehicleAllocator.cpp
        VehicleAllocator.h)
