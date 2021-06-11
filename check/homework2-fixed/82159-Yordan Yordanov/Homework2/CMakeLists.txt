cmake_minimum_required(VERSION 3.17)
project(Homework2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Homework2 main.cpp
        Headers/Registration.h Headers/Person.h Headers/Vehicle.h Headers/CommandParser.h
        Sources/Registration.cpp Sources/Person.cpp Sources/Vehicle.cpp Sources/CommandParser.cpp )

add_executable(Test Tests/main.cpp
        Catch2/catch2.h Catch2/catch2.cpp
        Headers/Registration.h Headers/Person.h Headers/Vehicle.h Headers/CommandParser.h
        Sources/Registration.cpp Sources/Person.cpp Sources/Vehicle.cpp Sources/CommandParser.cpp)