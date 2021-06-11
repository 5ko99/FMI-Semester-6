# CMakeLists.txt

cmake_minimum_required(VERSION 3.16)  
project(Homework DESCRIPTION "Homework2 for FMI 2021 OOP course" VERSION 0.0.1)

message("Finding 3d-party Catch2 library")
find_package(Catch2 CONFIG REQUIRED)

message("Creating target for main")
add_executable(main src/main.cpp src/Vehicle.cpp src/Person.cpp src/Registration.cpp src/Executor.cpp src/UnaryCommand.cpp src/BinaryCommand.cpp)
target_compile_features(main PUBLIC cxx_std_17)

message("Creating target for test of the Registration class")
add_executable(run_RegistrationTests src/Registration.cpp tests/RegistrationTests.cpp )
target_compile_features(run_RegistrationTests PUBLIC cxx_std_17)
target_link_libraries(run_RegistrationTests PRIVATE Catch2::Catch2)

message("Creating a test target for Person and Vehicle")
add_executable(run_PersonVehicleTests src/Vehicle.cpp src/Person.cpp src/Registration.cpp  tests/PersonVehicleTests.cpp)
target_compile_features(run_PersonVehicleTests PUBLIC cxx_std_17)
target_link_libraries(run_PersonVehicleTests PRIVATE Catch2::Catch2)

enable_testing()
add_test(RegistrationTests run_RegistrationTests)
add_test(PersonVehicleTests run_PersonVehicleTests)
message("Build successfully")