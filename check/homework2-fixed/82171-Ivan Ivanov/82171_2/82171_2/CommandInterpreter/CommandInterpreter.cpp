#include "CommandInterpreter.h"
#include "../FileHandlers/FileReader/FileReader.h"
#include "../FileHandlers/FileWriter/FileWriter.h"
#include <iostream>

bool CommandInterpreter::confirmCommand() {
    std::cout << "Are you sure u want to execute the command(Y/N): ";
    char c;
    std::cin >> c;
    if (c == 'Y' || c == 'y') {
        return true;
    }
    else if (c == 'N' || c == 'n') {
        return false;
    }
    else {
        std::cout << "Invalid input, command will not execute.";
        int numCharIgnored = 10000;
        std::cin.ignore(numCharIgnored, '\n');
    }
    return false;
}

void CommandInterpreter::toLower(std::string& str) {
    for (std::size_t i = 0; i < str.length(); ++i) {
        str[i] = tolower(str[i]);
    }
}

void CommandInterpreter::removeAdditionalSpaces(std::string& str) {
    char alteredStr[str.length()];
    std::size_t write = 0;
    std::size_t read = 0;
    bool isSpaced = true;
    
    // Removes all additional spaces except one space at the end (if there is such)
    while (read < str.length()) {
        if (isSpaced == true && str[read] != ' ') {
            isSpaced = false;
            alteredStr[write] = str[read];
            ++write;
        }
        else if (isSpaced == false) {
            alteredStr[write] = str[read];

            if (read != str.length() - 1 && str[read] == ' ') {
                isSpaced = true;
            }

            ++write;
        }
        ++read;
    }

    // If the last char is ' ', it is not coppied
    if (alteredStr[write - 1] == ' ') {
        --write;
    }

    str.assign(alteredStr, write);
}

void CommandInterpreter::splitInArray(std::string str, std::string commPar[]) {
    std::size_t numParam = 0;
    std::size_t indexBegin = 0;
    bool isInQuotes = false;
    for (std::size_t i = 0; i < str.length(); ++i) {
        if (isInQuotes == true) {
            if (str[i] == '\"') {
                isInQuotes = false;
                commPar[numParam] = str.substr(indexBegin, i - indexBegin);
                ++numParam;
                if (i < str.length() - 1 && str[i + 1] == ' ') {
                    ++i;
                }
                indexBegin = i + 1;
            }
        }
        else {
            if (str[i] == '\"') {
                isInQuotes = true;
                indexBegin = i + 1;
            }
            else if (str[i] == ' ') {
                commPar[numParam] = str.substr(indexBegin, i - indexBegin);
                ++numParam;
                indexBegin = i + 1;
            }
            else if (i == str.length() - 1) {
                commPar[numParam] = str.substr(indexBegin, i - indexBegin + 1);
            }
        }
    }
}

void CommandInterpreter::formatCommand(std::string commandAndParameters, std::string commPar[]) {
    removeAdditionalSpaces(commandAndParameters);
    splitInArray(commandAndParameters, commPar);
    toLower(commPar[0]);
    
    // Removes additional spaces from words in quotes
    for (std::size_t i = 1; i <= MAX_NUMBER_PARAMETERS; ++i) {
        removeAdditionalSpaces(commPar[i]);
    }
}

void CommandInterpreter::callFunction(std::string commPar[], PersonHolder* pH, VehicleHolder* vH) {
    if (commPar[0] == "vehicle") {
        if (Registration::isValid(commPar[1]) == false) {
            throw RegistrationException("Invalid registration.");
        }
        vH->add(Vehicle(Registration(commPar[1]), commPar[2]));
    }
    else if (commPar[0] == "person") {
        pH->add(Person(commPar[1], atoi(commPar[2].c_str())));
    }
    else if (commPar[0] == "acquire") {
        OwnershipController::acquireVehicle(vH->getByRegistration(Registration(commPar[2])),
            pH->getByID(atoi(commPar[1].c_str())));
    }
    else if (commPar[0] == "release") {
        OwnershipController::releaseVehicle(vH->getByRegistration(Registration(commPar[2])),
            pH->getByID(atoi(commPar[1].c_str())));
    }
    else if (commPar[0] == "save") {
        FileWriter::writeToFile(commPar[1], pH, vH);
    }
    else if (commPar[0] == "remove") {
        if (Registration::isValid(commPar[1])) {
            OwnershipController::releaseVehicle(vH->getByRegistration(Registration(commPar[1])));
            vH->removeByRegistration(Registration(commPar[1]));
        }
        else {
            OwnershipController::releaseVehiclesOf(pH->getByID(atoi(commPar[1].c_str())));
            pH->removeByID(atoi(commPar[1].c_str()));
        }
    }
    else if (commPar[0] == "show") {
        toLower(commPar[1]);
        if (commPar[1] == "people") {
            pH->printAll();
        }
        else if (commPar[1] == "vehicles") {
            vH->printAll();
        }
        else if ((Registration::isValid(commPar[1]))) {
            vH->printDetailed(Registration(commPar[1]));
        }
        else {
            pH->printDetailed(atoi(commPar[1].c_str()));
        }
    }
    else if (commPar[0] == "end") {
        throw EndException("End command registered. Program will exit.");
    }
}

void CommandInterpreter::execute(std::string commandAndParameters, PersonHolder* pH, VehicleHolder* vH) {
    std::string commPar[MAX_NUMBER_PARAMETERS + 1];
    formatCommand(commandAndParameters, commPar);

    callFunction(commPar, pH, vH);
}
