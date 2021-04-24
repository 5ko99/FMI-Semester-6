cmake_minimum_required(VERSION 3.19)
project(hom)

set(CMAKE_CXX_STANDARD 14)

include_directories(main)

add_executable(hom
        main/garage.cpp
        main/garage.h
        main/main.cpp
        main/mystring.cpp
        main/mystring.h
        main/vector.cppa
        main/vector.h
        main/vehicle.cpp
        main/vehicle.h)
