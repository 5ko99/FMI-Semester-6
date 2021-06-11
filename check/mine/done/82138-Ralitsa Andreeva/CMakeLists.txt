cmake_minimum_required(VERSION 3.19)
project(82138_Ralitsa_Andreeva)

set(CMAKE_CXX_STANDARD 14)

include_directories(hw2)

add_executable(82138_Ralitsa_Andreeva
        hw2/Command.cpp
        hw2/Command.h
        hw2/Database.cpp
        hw2/Database.h
        hw2/Helpers.cpp
        hw2/Helpers.h
        hw2/HW2.cpp
        hw2/Person.cpp
        hw2/Person.h
        hw2/Registration.cpp
        hw2/Registration.h
        hw2/Vehicle.cpp
        hw2/Vehicle.h)
