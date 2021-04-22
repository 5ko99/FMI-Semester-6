cmake_minimum_required(VERSION 3.19)
project(exm)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(exm
        catch2.cpp
        catch2.hpp
        Garage.cpp
        Garage.h
        main_Homework.cpp
        MyString.cpp
        MyString.h
        Vehicle.cpp
        Vehicle.h)
