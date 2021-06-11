#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

#include "../Headers/CommandHandler.h"
#include "../Headers/PersonCollection.h"
#include "../Headers/VehicleCollection.h"

void CommandHandler::readFromFile(std::string &path,
                                  PersonCollection &personCollection,
                                  VehicleCollection &vehicleCollection) {
    // Open inFile
    std::ifstream inFile(path);
    if (!inFile) {
        std::cout << "Cannot open file with path: " << path << '\n'
                  << "Starting with an empty database\n";
        return;
    }

    std::string inputStr;
    std::string commandStr;
    do {
        inFile >> commandStr;
        // Commands are case insensitive
        // Convert to lower case string
        transform(commandStr.begin(), commandStr.end(), commandStr.begin(), ::tolower);

        if (commandStr == "vehicle") {
            // <registration> argument
            std::string registration;
            inFile >> registration;

            // <description> argument
            std::string description;
            inFile >> description;

            Registration vehicleId(registration);
            Vehicle vehicle(vehicleId, description);
            vehicleCollection.addVehicle(vehicle);

        } else if (commandStr == "person") {
            // <name> argument
            std::string firstName;
            std::string lastName;
            inFile >> firstName >> lastName;
            // <description> argument
            std::string idStr;
            inFile >> idStr;

            unsigned int id = std::stoi(idStr);

            // TODO Check if it throws
            Person person(firstName + " " + lastName, id);
            personCollection.addPerson(person);

        } else if (commandStr == "acquire") {
            // <owner-id> argument
            std::string ownerIdStr;
            inFile >> ownerIdStr;
            // <vehicle-id> argument
            std::string vehicleId;
            inFile >> vehicleId;

            unsigned int ownerId = std::stoi(ownerIdStr);
            personCollection.acquireVehicle(ownerId, Registration(vehicleId),
                                            vehicleCollection);
        }
    } while (!inFile.eof());
    // Close inFile
    inFile.close();

    std::cout << "Data is successfully read from file with path: " << path << "\n";
}

void CommandHandler::readFromConsole(PersonCollection &personCollection,
                                     VehicleCollection &vehicleCollection) {

    std::cout << "The program is now reading data from console!\n"
              << "You can now read/write new data...\n";

    bool dataIsSaved = false;

    do {
        std::cin.getline(m_input, MAX_INPUT);
        m_command = std::strtok(m_input, " ");

        // Commands are case insensitive
        toLower(m_command);

        if (!strcmp(m_command, "vehicle")) {
            // <registration> argument
            char *registration = std::strtok(nullptr, " ");
            // <description> argument
            char *description = std::strtok(nullptr, " ");

            // Now we cannot distinct which one of those throws
            // But the user is alerted (with not very detailed info...)
            try {
                Registration vehicleId(registration);
                Vehicle vehicle(vehicleId, description);
                vehicleCollection.addVehicle(vehicle);
                std::cout << "Vehicle is added to collection!\n";
            } catch (std::invalid_argument &ex) {
                std::cout << "Invalid input!\n"
                          << "Make sure that the data complies with the requirements and vehicle's id is unique\n";
            }

        } else if (!strcmp(m_command, "person")) {
            // <name> argument
            char *name = std::strtok(nullptr, "\"");
            // <id> argument
            char *idStr = std::strtok(nullptr, " ");

            unsigned int id = std::atoi(idStr);

            try {
                Person person(name, id);
                personCollection.addPerson(person);
                std::cout << "Person is added to collection!\n";

            } catch (std::invalid_argument &ex) {
                std::cout << "Invalid input!\n"
                          << "Make sure that the data complies with the requirements and person's id is unique\n";
            }

        } else if (!strcmp(m_command, "acquire")) {
            // <owner-id> argument
            char *ownerIdStr = std::strtok(nullptr, " ");
            // <vehicle-id> argument
            char *vehicleId = std::strtok(nullptr, " ");

            try {
                unsigned int ownerId = std::atoi(ownerIdStr);
                personCollection.acquireVehicle(ownerId, Registration(vehicleId),
                                                vehicleCollection);
                std::cout << "Vehicle now has an owner!\n";
            } catch (std::invalid_argument &ex) {
                std::cout << "Invalid input!\n"
                          << "Make sure that the data complies with the requirements\n";
            }

        } else if (!strcmp(m_command, "release")) {
            // <owner-id> argument
            char *ownerIdStr = std::strtok(nullptr, " ");
            // <vehicle-id> argument
            char *vehicleId = std::strtok(nullptr, " ");

            unsigned int ownerId = std::atoi(ownerIdStr);
            try {
                personCollection.releaseVehicle(ownerId, Registration(vehicleId));
                std::cout << "Vehicle is released!\n";
            } catch (std::invalid_argument &ex) {
                std::cout << "Invalid input - there is no person/vehicle with that id!\n"
                          << "Make sure that the data complies with the requirements\n";
            }

        } else if (!strcmp(m_command, "remove")) {
            // <what> argument - may be <owner-id> or <vehicle-id>
            char *what = std::strtok(nullptr, " ");

            // Determine if input is about Person obj or Vehicle obj
            if (isAlpha(what[0])) {
                try {
                    // Each <vehicle-id> starts with letter, so it is probably <vehicle-id>
                    vehicleCollection.removeVehicle(Registration(what),
                                                    personCollection);
                    std::cout << "Vehicle is removed from collection!\n";
                } catch (std::invalid_argument &ex) {
                    std::cout << "Invalid input - there is no vehicle with that id!\n";
                }

            } else {
                unsigned int ownerId = std::atoi(what);
                try {
                    personCollection.removePerson(ownerId);
                    std::cout << "Vehicle is removed from collection!\n";

                } catch (std::invalid_argument &ex) {
                    std::cout << "Invalid input - there is no person with that id!\n";
                }
            }

        } else if (!strcmp(m_command, "show")) {
            char *argument = std::strtok(nullptr, " ");
            toLower(argument);
            if (!strcmp(argument, "people")) {
                std::cout << personCollection;

            } else if (!strcmp(argument, "vehicles")) {
                std::cout << vehicleCollection;

            } else if (isAlpha(argument[0])) {
                // Each <vehicle-id> starts with letter, so it is probably <vehicle-id>
                /* vehicleCollection.removeVehicle(Registration(what),
                                                 personCollection);*/
                vehicleCollection.showVehicleDetails(Registration(argument));

            } else if (std::atoi(argument) != 0) {
                unsigned int ownerId = std::atoi(argument);
                personCollection.showPersonDetails(ownerId);

            } else {
                std::cout << "Invalid argument for \"show\" command! Please, try again\n";
            }

        } else if (!strcmp(m_command, "save")) {
            // <path> argument
            char *path = std::strtok(nullptr, " ");
            saveToFile(path, personCollection, vehicleCollection);
            dataIsSaved = true;
            std::cout << "Entered data is now saved in file with path: "
                      << path << "\n";

        } else if (!strcmp(m_command, "quit")) {
            if (dataIsSaved) {
                std::cout << "Terminating the program...\n";
                break;
            }
            std::cout << "Data is not saved in a file!\n"
                      << "Please save your data before terminating the program\n";
        } else {
            std::cout << "Invalid command! Please, try again\n";
        }
    } while (strcmp(m_command, "quit") != 0 ||
             !dataIsSaved);
}

void CommandHandler::saveToFile(char *path,
                                const PersonCollection &personCollection,
                                const VehicleCollection &vehicleCollection) {
    std::ofstream outFile(path);
    // Check if file is opened correctly
    if (!outFile) {
        std::cout << "Cannot open file with path: " << path << "\n";
    }
    unsigned int peopleCount = personCollection.peopleCount();
    for (int i = 0; i < peopleCount; ++i) {
        outFile << "person " << personCollection[i]
                << '\n';
    }

    unsigned int vehiclesCount = vehicleCollection.vehiclesCount();
    for (int i = 0; i < peopleCount; ++i) {
        outFile << "vehicle " << vehicleCollection[i]
                << '\n';
    }

    for (int personIndex = 0; personIndex < peopleCount; ++personIndex) {
        vehiclesCount = personCollection[personIndex].getVehiclesCount();
        for (int vehicleIndex = 0; vehicleIndex < vehiclesCount; ++vehicleIndex) {
            outFile << "acquire "
                    << personCollection[personIndex].getId()
                    << " "
                    << personCollection[personIndex].getVehicle(vehicleIndex)->getRegistration()
                    << '\n';

        }
    }
    // Close file
    outFile.close();
}

void CommandHandler::toLower(char *string) {
    if (!string) {
        std::cout << "Invalid string!\n";
        return;
    }

    size_t indexLetter = 0;
    while (string[indexLetter] != '\0') {
        if (isAlpha(string[indexLetter])
            && isUpper(string[indexLetter])) {
            string[indexLetter] += 'a' - 'A';
        }
        ++indexLetter;
    }
}

bool CommandHandler::isUpper(char letter) {
    return (letter >= 'A' && letter <= 'Z');
}

bool CommandHandler::isAlpha(char symbol) {
    return (symbol >= 'a' && symbol <= 'z')
           || (symbol >= 'A' && symbol <= 'Z');
}
