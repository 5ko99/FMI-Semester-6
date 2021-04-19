cmake_minimum_required(VERSION 3.19)
project(test1)

set(CMAKE_CXX_STANDARD 20)

add_executable(test1 main.cpp Registration.cpp Registration.h Vehicle.cpp Vehicle.h VehicleList.cpp VehicleList.h)