cmake_minimum_required(VERSION 3.19)
project(Homework_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Homework_2 main.cpp
        Sources/Registration.cpp Headers/Registration.h
        Sources/Person.cpp Headers/Person.h Sources/Vehicle.cpp
        Headers/Vehicle.h Sources/PersonCollection.cpp Headers/PersonCollection.h Sources/VehicleCollection.cpp Headers/VehicleCollection.h Tests/PersonCollectionTests.cpp Sources/CommandHandler.cpp Headers/CommandHandler.h Tests/VehicleCollectionTests.cpp)