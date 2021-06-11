#include "..\Headers\Command.hpp"

//! Command constructor with reference to Person and Vehicle vectors from main()
Command::Command(std::vector<Person>* peopleInput, std::vector<Vehicle>* vehiclesInput) {
    people = peopleInput;
    vehicles = vehiclesInput;
}

//! Function to set the command line
///< Used as a part of the file reading function
void Command::setCommandLine(char commandLineInput[256]) {
    strcpy(commandLine, commandLineInput);
    verifyCmd();
}

//! Function to set the command line
///< Used as a part of the reading from file function
int Command::inputCmd() {
    std::cout << ">";
    std::cin.getline(commandLine, 256, '\n');
    return verifyCmd();
}

int Command::verifyCmd() {
    char operation[SIZE_OPERATION];
    int typeOfOperation = 0;
    unsigned short int index = 0;

    while (commandLine[index] != ' ' && index <= 7) {
        operation[index] = commandLine[index];
        ++index;
    }
    operation[index] = '\0';

    for (unsigned short int i = 0; i < std::strlen(operation); ++i) {
        if (operation[i] >= 'a' && operation[i] <= 'z') {
            operation[i] -= 32;
        }
        if (operation[i] < 'A' || operation[i] > 'Z') {
            throw std::invalid_argument("[!] Error in operation verification!\n    The operation consists only of letters!\n");
        }
    }

    for (unsigned int i = 1; i < COUNTOPERATIONS; i++) {
        if (strcmp(operation, operationList[i]) == 0) {
            typeOfOperation = i;
        }
    }

    // if (typeOfOperation == 0) {
    //     throw std::invalid_argument("[!] Error in operation verification!\n    The operation is undefined!\n");
    // }

    ++index;
    char commandParameter1[SIZE_OPERATION_PARAM] = {" "};
    unsigned short int indexParam1 = 0;
    char breaker = ' ';

    while (commandLine[index] == ' ') {
        ++index;
    }

    if (commandLine[index] == '"') {
        ++index;
        breaker = '"';
    }

    indexParam1 = index;
    while (commandLine[index] != breaker && commandLine[index] != '\0') {
        commandParameter1[index - indexParam1] = commandLine[index];
        ++index;
    }
    commandParameter1[index - indexParam1] = '\0';

    if (commandLine[index] == '"') {
        ++index;
    }
    while (commandLine[index] == ' ') {
        ++index;
    }

    char commandParameter2[SIZE_OPERATION_PARAM] = {" "};
    unsigned short int indexParam2 = 0;
    bool existingParameter2 = true;
    if (commandLine[index] == '\0') {
        existingParameter2 = false;
    } else {
        breaker = ' ';
        if (commandLine[index] == '"') {
            ++index;
            breaker = '"';
        }

        indexParam2 = index;
        while (commandLine[index] != breaker && commandLine[index] != '\0') {
            commandParameter2[index - indexParam2] = commandLine[index];
            ++index;
        }
        commandParameter2[index - indexParam2] = '\0';
    }
    // std::cout << "Operation " << operation << "|" << commandParameter1 << "|" << commandParameter2 << std::endl;
    return executeCmd(typeOfOperation, commandParameter1, commandParameter2);
}

int Command::executeCmd(int typeOfOperation,
                        char commandParameter1[SIZE_OPERATION_PARAM],
                        char commandParameter2[SIZE_OPERATION_PARAM]) {
    switch (typeOfOperation) {
        //! VEHICLE <registration> <description>
        case VEHICLE:
            createVehicle(commandParameter1, commandParameter2);
            break;

        //! PERSON <name> <id>
        case PERSON:
            createPerson(commandParameter1, commandParameter2);
            break;

        //! ACQUIRE <owner-id> <vehicle-id>
        case AQUIRE:
            aquireVehicle(commandParameter1, commandParameter2);
            break;

        //! RELEASE <owner-id> <vehicle-id>
        case RELEASE:
            releaseVehicle(commandParameter1, commandParameter2);
            break;

        //! REMOVE <what>
        case REMOVE:
            removeData(commandParameter1);
            break;

        //! SAVE <path>
        case SAVE:
            saveFile(commandParameter1);
            break;

        //!SHOW [PEOPLE|VEHICLES|<id>]
        case SHOW:
            showData(commandParameter1);
            return 0;
            break;

        //! EXIT
        case EXIT:
            return 1;
            break;

            // default:
            //     return 1;
            //     break;
    }
    return 0;
}

void Command::loadFromFile(char* argvInput) {
    char commandLineHold[256] = "Example";
    std::ifstream fileInput;
    fileInput.open(argvInput, std::ios::in);
    while (fileInput.getline(commandLineHold, SIZE_COMMAND_LINE, '\n')) {
        setCommandLine(commandLineHold);
    }
    fileInput.close();
    std::cout << "(!) Successfully loaded data from file:" << argvInput << "!\n";
}

void Command::createVehicle(char registrationString[SIZE_OPERATION_PARAM], char descriptionString[SIZE_OPERATION_PARAM]) {
    try {
        vehicles->push_back(Vehicle(registrationString, descriptionString));
    } catch (const std::invalid_argument& e) {
        std::cout << e.what();
    }
}

void Command::createPerson(char nameString[SIZE_OPERATION_PARAM], char idNumber[SIZE_OPERATION_PARAM]) {
    unsigned int identifierPerson = 0;
    unsigned int i = 0;
    while (idNumber[i] != '\0') {
        identifierPerson *= 10;
        identifierPerson += (idNumber[i] - '0');
        ++i;
    }

    try {
        people->push_back(Person(nameString, identifierPerson));
    } catch (const std::invalid_argument& e) {
        std::cout << e.what();
    }
}

void Command::aquireVehicle(char ownerData[SIZE_OPERATION_PARAM], char vehicleData[SIZE_OPERATION_PARAM]) {
    unsigned int identifierPerson = 0;
    unsigned int i = 0;
    while (ownerData[i] != '\0') {
        identifierPerson *= 10;
        identifierPerson += (ownerData[i] - '0');
        ++i;
    }

    for (int j = 0; j < people->size(); j++) {
        if (people->at(j).getIdentifier() == identifierPerson) {
            for (int k = 0; k < vehicles->size(); k++) {
                if (std::strcmp(vehicles->at(k).getRegistration().getRegistration(), vehicleData) == 0) {
                    if (vehicles->at(k).getOwner() != nullptr) {
                        vehicles->at(k).getOwner()->releaseVehicle(vehicleData);
                    }
                    people->at(j).acquireVehicleToPerson(&vehicles->at(k));
                    vehicles->at(k).acquireVehicle(&people->at(j));
                }
            }
        }
    }
}

void Command::releaseVehicle(char ownerData[SIZE_OPERATION_PARAM], char vehicleData[SIZE_OPERATION_PARAM]) {
    unsigned int identifierPerson = 0;
    unsigned int i = 0;
    while (ownerData[i] != '\0') {
        identifierPerson *= 10;
        identifierPerson += (ownerData[i] - '0');
        ++i;
    }

    //! Verification if the person and the vehicle exist
    bool personExistVerification = false;
    bool vehicleExistVerification = false;
    bool personOwnsVehicleVerification = false;

    for (int j = 0; j < people->size(); ++j) {
        if (people->at(j).getIdentifier() == identifierPerson) {
            personExistVerification = true;
            for (int k = 0; k < vehicles->size(); ++k) {
                if (std::strcmp(vehicles->at(k).getRegistration().getRegistration(), vehicleData) == 0) {
                    vehicleExistVerification = true;
                    for (size_t l = 0; l < people->at(j).getOwnedVehicles().size(); ++l) {
                        if (std::strcmp(people->at(j).getOwnedVehicles().at(l)->getRegistration().getRegistration(), vehicleData) == 0) {
                            personOwnsVehicleVerification = true;
                            vehicles->at(k).freeVehicle();
                            people->at(j).releaseVehicle(vehicleData);
                        }
                    }
                }
            }
        }
    }

    if (personExistVerification == true) {
        if (vehicleExistVerification == true) {
            if (personOwnsVehicleVerification == true) {
                std::cout << "(!) Successfully released vehicle with registration:" << vehicleData
                          << " from person with ID:" << identifierPerson << "!\n";
            } else {
                std::cout << "[!] The person with ID:" << identifierPerson
                          << " does not own the vehicle with registration:" << vehicleData << "!\n";
            }
        } else {
            std::cout << "[!] Vehicle with registration:" << vehicleData << " does not exist in the database!\n";
        }
    } else {
        std::cout << "[!] Person with ID:" << identifierPerson << " does not exist in the database!\n";
    }
}

void Command::removeData(char removeData[SIZE_OPERATION_PARAM]) {
    if (removeData[0] >= '0' && removeData[0] <= '9') {
        //! Removing a person
        unsigned int identifierPerson = 0;
        unsigned int i = 0;
        while (removeData[i] != '\0') {
            identifierPerson *= 10;
            identifierPerson += (removeData[i] - '0');
            ++i;
        }
        bool flagFound = false;
        int indexOfSearchedPerson = 0;
        for (int j = 0; j < people->size(); ++j) {
            if (people->at(j).getIdentifier() == identifierPerson) {
                flagFound = true;
                indexOfSearchedPerson = j;
            }
        }
        if (flagFound == true) {
            if (people->at(indexOfSearchedPerson).getOwnedVehicles().size() > 0) {
                char answerYesNo[4] = "NO";

                do {
                    std::cout << "<?> The person you want to remove owns at least one vehicle! Do you want to delete the data? (YES / NO)\n";
                    std::cout << "(YES/NO) > ";
                    std::cin >> answerYesNo;
                } while (!(std::strcmp(answerYesNo, "YES") == 0 || std::strcmp(answerYesNo, "yes") == 0 ||
                           std::strcmp(answerYesNo, "NO") == 0 || std::strcmp(answerYesNo, "no") == 0));

                if (std::strcmp(answerYesNo, "YES") == 0 || std::strcmp(answerYesNo, "yes") == 0) {
                    for (int k = 0; k < people->at(indexOfSearchedPerson).getOwnedVehicles().size(); ++k) {
                        people->at(indexOfSearchedPerson).getOwnedVehicles().at(k)->freeVehicle();
                    }
                    people->erase(people->begin() + indexOfSearchedPerson);
                    std::cout << "(!) Successfully deleted person with ID:" << identifierPerson << "!\n";
                } else if (std::strcmp(answerYesNo, "NO") == 0 || std::strcmp(answerYesNo, "no") == 0) {
                    std::cout << "(!) Operation aborted! No data was deleted!\n";
                }
            } else {
                people->erase(people->begin() + indexOfSearchedPerson);
            }
        }
        if (flagFound == false) {
            std::cout << "[!] Person with ID:" << identifierPerson << " does not exist in the database!\n";
        }

    } else {
        //! Removing a vehicle
        unsigned short int index = 0;
        while (removeData[index] != '\0') {
            if (removeData[index] >= 'a' && removeData[index] <= 'z') {
                removeData[index] -= 32;
            }
            ++index;
        }
        if (isARegistration(removeData)) {
            bool flagFound = false;
            int indexOfSearchedVehicle = 0;

            for (int i = 0; i < vehicles->size(); ++i) {
                if (std::strcmp(vehicles->at(i).getRegistration().getRegistration(), removeData) == 0) {
                    flagFound = true;
                    indexOfSearchedVehicle = i;
                }
            }

            if (flagFound == true) {
                if (vehicles->at(indexOfSearchedVehicle).getOwner() != nullptr) {
                    char answerYesNo[4];
                    do {
                        std::cout << "<?> The vehicle you want to remove has an owner! Do you want to delete the data? (YES / NO)\n";
                        std::cout << "(YES/NO) > ";
                        std::cin >> answerYesNo;
                    } while (!(std::strcmp(answerYesNo, "YES") == 0 || std::strcmp(answerYesNo, "yes") == 0 ||
                               std::strcmp(answerYesNo, "NO") == 0 || std::strcmp(answerYesNo, "no") == 0));

                    if (std::strcmp(answerYesNo, "YES") == 0 || std::strcmp(answerYesNo, "yes") == 0) {
                        for (unsigned int i = 0; i < people->size(); ++i) {
                            people->at(i).emptyVehicle();
                        }

                        vehicles->erase(vehicles->begin() + indexOfSearchedVehicle);
                        for (unsigned int i = 0; i < vehicles->size(); ++i) {
                            for (unsigned int j = 0; j < people->size(); ++j) {
                                if (vehicles->at(i).getOwner() != nullptr) {
                                    if (vehicles->at(i).getOwner()->getIdentifier() == people->at(j).getIdentifier()) {
                                        people->at(j).acquireVehicleToPerson(&vehicles->at(i));
                                    }
                                }
                            }
                        }
                        std::cout << "(!) Successfully deleted vehicle with registration:" << removeData << "!\n";
                    }

                    if (std::strcmp(answerYesNo, "NO") == 0 || std::strcmp(answerYesNo, "no") == 0) {
                        std::cout << "(!) Operation aborted! No data was deleted!\n";
                    }

                } else {
                    vehicles->erase(vehicles->begin() + indexOfSearchedVehicle);
                }
            }
            if (flagFound == false) {
                std::cout << "(!) Vehicle with registration:" << removeData << " does not exist in the database!\n";
            }
        }
    }
}

void Command::saveFile(char savePath[SIZE_OPERATION_PARAM]) {
    std::ofstream fileOutput;
    fileOutput.open(savePath, std::ios::out);
    for (int i = 0; i < people->size(); ++i) {
        fileOutput << "PERSON \"" << people->at(i).getName() << "\" " << people->at(i).getIdentifier() << "\n";
    }
    for (int i = 0; i < vehicles->size(); ++i) {
        fileOutput << "VEHICLE " << vehicles->at(i).getRegistration().getRegistration() << " \"" << vehicles->at(i).getDescription() << "\"\n";
    }
    for (int i = 0; i < vehicles->size(); ++i) {
        if (vehicles->at(i).getOwner() != nullptr) {
            fileOutput << "AQUIRE " << vehicles->at(i).getOwner()->getIdentifier() << ' ' << vehicles->at(i).getRegistration().getRegistration() << "\n";
        }
    }
    std::cout << "(!) Successfully saved database as file:" << savePath << "!\n";
    fileOutput.close();
}

void Command::showData(char searchData[SIZE_OPERATION_PARAM]) {
    if (searchData[0] >= '0' && searchData[0] <= '9') {
        unsigned int identifierPerson = 0;
        unsigned int i = 0;
        while (searchData[i] != '\0') {
            identifierPerson *= 10;
            identifierPerson += (searchData[i] - '0');
            ++i;
        }
        for (unsigned int j = 0; j < people->size(); ++j) {
            if (people->at(j).getIdentifier() == identifierPerson) {
                if (people->at(j).getOwnedVehicles().size() > 0) {
                    std::cout << "Owned vehicles: \n";
                    for (int k = 0; k < people->at(j).getOwnedVehicles().size(); ++k) {
                        std::cout << people->at(j).getOwnedVehicles().at(k)->getRegistration().getRegistration() << " \n";
                    }
                    break;
                }
            }
        }
    } else {
        unsigned short int index = 0;
        while (searchData[index] != '\0') {
            if (searchData[index] >= 'a' && searchData[index] <= 'z') {
                searchData[index] -= 32;
            }
            ++index;
        }
        if (std::strcmp(searchData, "VEHICLES") == 0) {
            std::cout << "Vehicles: \n";
            for (int i = 0; i < vehicles->size(); ++i) {
                std::cout << "Registration: " << vehicles->at(i).getRegistration().getRegistration() << "  Description: " << vehicles->at(i).getDescription() << "\n";
            }
        }
        if (std::strcmp(searchData, "PEOPLE") == 0) {
            std::cout << "People: \n";
            for (int i = 0; i < people->size(); ++i) {
                std::cout << "ID: " << people->at(i).getIdentifier() << "  Name: " << people->at(i).getName() << "\n";
            }
        }
        if (isARegistration(searchData)) {
            for (int i = 0; i < vehicles->size(); ++i) {
                if (std::strcmp(vehicles->at(i).getRegistration().getRegistration(), searchData) == 0) {
                    if (vehicles->at(i).getOwner() != nullptr) {
                        std::cout << "Owner: " << vehicles->at(i).getOwner()->getIdentifier() << "\n";
                    }
                }
            }
        }
    }
}
