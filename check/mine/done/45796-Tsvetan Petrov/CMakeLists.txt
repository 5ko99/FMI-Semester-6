cmake_minimum_required(VERSION 3.19)
project(45796_Tsvetan_Petrov)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(45796_Tsvetan_Petrov
        Instruction.cpp
        Instruction.h
        Person.cpp
        Person_Header.h
        Registration.cpp
        Registration_Header.h
        Source.cpp
        Vehicle.cpp
        Vehicle_Header.h)
