cmake_minimum_required(VERSION 3.19)
project(homework1_81977)

set(CMAKE_CXX_STANDARD 14)

include_directories(catch2)
include_directories(Garage)
include_directories(MyString)
include_directories(Vehicle)

add_executable(homework1_81977
        Garage/Garage.cpp
        Garage/Garage.h
        MyString/MyString.cpp
        MyString/MyString.h
        Vehicle/Vehicle.cpp
        Vehicle/Vehicle.h
        main.cpp)
