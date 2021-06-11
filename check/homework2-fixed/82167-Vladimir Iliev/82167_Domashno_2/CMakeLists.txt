cmake_minimum_required(VERSION 3.19)
project(Domashno_2)

set(CMAKE_CXX_STANDARD 20)

include_directories(Registration
        Registration/Tests
        C:/Users/User/Desktop/OOP/Git
        Person
        Person/Tests
        Vehicle
        Vehicle/Tests
        "Commands And Container"
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/Executables and others")

set(Registration_SRC
        Registration/Registration.cpp)

set(Person_SRC
        Person/Person.cpp)

set(Vehicle_SRC
        Vehicle/Vehicle.cpp)

set(Commands_And_Container_SRC
        "Commands And Container/Commands.cpp"
        "Commands And Container/Container.cpp")

add_executable(Main
        main.cpp
        ${Registration_SRC}
        ${Person_SRC}
        ${Vehicle_SRC}
        ${Commands_And_Container_SRC})

add_executable(Registration_Tests
        ${Registration_SRC}
        Registration/Tests/Registration_Tests.cpp)

add_executable(Person_Tests
        ${Registration_SRC}
        ${Vehicle_SRC}
        ${Person_SRC}
        Person/Tests/Person_Tests.cpp)

add_executable(Vehicle_Tests
        ${Registration_SRC}
        ${Vehicle_SRC}
        ${Person_SRC}
        Vehicle/Tests/Vehicle_Tests.cpp)

add_executable(C_and_C_Tests
        "Commands And Container/Tests/C_and_C_Tests.cpp"
        ${Registration_SRC}
        ${Vehicle_SRC}
        ${Person_SRC}
        ${Commands_And_Container_SRC})