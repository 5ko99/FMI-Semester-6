cmake_minimum_required(VERSION 3.19)
project(Homework2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Homework2 main.cpp Registration.h Person.h Vehicle.h registration.cpp person.cpp vehicle.cpp Command.h command.cpp)