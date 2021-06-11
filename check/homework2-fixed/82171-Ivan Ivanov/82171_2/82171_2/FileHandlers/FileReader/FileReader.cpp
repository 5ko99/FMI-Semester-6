#include "FileReader.h"
#include "../../CommandInterpreter/CommandInterpreter.h"
#include <iostream>

void FileReader::generateFromFile(std::string fileAddress, PersonHolder* pH, VehicleHolder* vH) {
    std::ifstream file(fileAddress);
    std::string command;
    while (std::getline(file, command)) {
        CommandInterpreter::execute(command, pH, vH);
    }
}
