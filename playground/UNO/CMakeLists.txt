cmake_minimum_required(VERSION 3.17)
project(UNO)

set(CMAKE_CXX_STANDARD 14)

include_directories("Header Files")

add_executable(UNO
        "Header Files/Card.h"
        "Header Files/Deck.h"
        "Header Files/Game.h"
        "Header Files/Player.h"
        "Source Files/Card.cpp"
        "Source Files/Deck.cpp"
        "Source Files/Game.cpp"
        "Source Files/Player.cpp"
        main.cpp)
