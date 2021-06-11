cmake_minimum_required(VERSION 3.19)
project(Homework2)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(Test)
add_executable(Homework2 main.cpp Headers/Registration.h Source/Registration.cpp Headers/Person.h
        Source/Person.cpp Headers/Vehicle.h Source/Vehicle.cpp Headers/Command.h Source/Command.cpp Headers/DataBase.h
        Source/DataBase.cpp)