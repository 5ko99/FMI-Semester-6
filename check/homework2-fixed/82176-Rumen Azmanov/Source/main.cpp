#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "..\Headers\Command.hpp"
#include "..\Headers\Person.hpp"
#include "..\Headers\Registration.hpp"
#include "..\Headers\Vehicle.hpp"

int main(int argc, char* argv[]) {
    std::vector<Person> people;
    std::vector<Vehicle> vehicles;
    int commandExit = 0;
    Command command(&people, &vehicles);

    if (argc == 2) {
        try {
            command.loadFromFile(argv[1]);
        } catch (const std::invalid_argument& e) {
            std::cout << e.what();
        }
    }

    try {
        while (commandExit != 1) {
            commandExit = command.inputCmd();
        }
    } catch (const std::invalid_argument& e) {
        std::cout << e.what();
    }

    return 0;
}

// NOTES!

// g++ .\main.cpp Registration.cpp Person.cpp Vehicle.cpp Command.cpp
// g++ .\CatchTests.cpp Registration.cpp Person.cpp Vehicle.cpp Command.cpp ..\catch2\catch2.cpp

// .\a.exe
// .\a.exe ../Data/Input.txt
