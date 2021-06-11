cmake_minimum_required(VERSION 3.19)
project(HW_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW_2
        Commander.cpp
        Commander.hpp
        main.cpp
        Organizer.cpp
        Organizer.hpp
        Person.cpp
        Person.hpp
        Registration.cpp
        Registration.hpp
        Vehicle.cpp
        Vehicle.hpp
        Verify.cpp
        Verify.hpp)
