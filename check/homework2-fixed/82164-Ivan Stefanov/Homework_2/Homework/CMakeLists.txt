cmake_minimum_required(VERSION 3.19)
project(Homework2)

set(CMAKE_CXX_STANDARD 14)

include_directories("Header Files" "Catch")

add_executable(Homework2
        "main.cpp"
        "Header Files/Registration.h"
        "Source Files/Registration.cpp"
        "Header Files/Person.h"
        "Source Files/Person.cpp"
        "Header Files/Vehicle.h"
        "Source Files/Vehicle.cpp"
        "Header Files/ProgramManager.h"
        "Source Files/ProgramManager.cpp")

