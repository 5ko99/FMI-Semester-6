add_executable(Homework02 src/main.cpp src/Commands.cpp src/commandTokenizer.cpp src/Person.cpp src/Registration.cpp src/Vehicle.cpp src/Database.cpp)
target_include_directories(Homework02 PRIVATE include/)

add_executable(Tests src/Commands.cpp src/commandTokenizer.cpp src/Person.cpp src/Registration.cpp src/Vehicle.cpp src/Database.cpp
                     tests/catch2.cpp tests/Person_Tests.cpp tests/Vehicle_Tests.cpp tests/Registration_Tests.cpp tests/Database_Tests.cpp)
target_include_directories(Tests PRIVATE include/)