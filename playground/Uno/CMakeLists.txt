cmake_minimum_required(VERSION 3.17)
project(Uno)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Uno
        CardBody.cpp
        Cards.h
        Game.cpp
        Game.h
        Player.cpp
        Player.h)
