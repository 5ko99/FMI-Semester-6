cmake_minimum_required(VERSION 3.19)
project(K_nn)

include_directories(Repository,
        Unit)

add_executable(K_nn main.cpp Unit/Unit.cpp Unit/Unit.h Repository/Repository.cpp Repository/Repository.h Algorithm/Algorithm.cpp Algorithm/Algorithm.h)