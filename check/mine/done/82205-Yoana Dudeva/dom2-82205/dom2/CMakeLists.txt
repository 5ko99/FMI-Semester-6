cmake_minimum_required(VERSION 3.19)
project(dom2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dom2
        commands.cpp
        commands.h
        exceptions.h
        main.cpp
        person.cpp
        person.h
        registration.cpp
        registration.h
        vehicle.cpp
        vehicle.h)

add_executable(Test
        catch2.cpp
        catch2.hpp
        unittests.cpp
        commands.cpp
        commands.h
        exceptions.h
        person.cpp
        person.h
        registration.cpp
        registration.h
        vehicle.cpp
        vehicle.h)