#include "PVDatabase.h"

PVDatabase::PVDatabase() {
    ;
}

void PVDatabase::printCommands() {
    std::cout << "------------------------------------\n";
    std::cout << "Commands supported:\n";
    std::cout << "VEHICLE <registration> <description>\n";
    std::cout << "PERSON <name> <id>\n";
    std::cout << "ACQUIRE <owner-id> <vehicle-id>\n";
    std::cout << "RELEASE <owner-id> <vehicle-id>\n";
    std::cout << "REMOVE <what>\n";
    std::cout << "SAVE <path>\n";
    std::cout << "SHOW [PEOPLE|VEHICLES|<id>]\n";
    std::cout << "END\n";
    std::cout << "------------------------------------\n";
    std::cout << std::endl;
}

void PVDatabase::setUp(int numParam, char* param[]) {
    if (numParam > 1) {
        FileReader::generateFromFile(param[1], *(this->pH), *(this->vH));
    }
    printCommands();
}

void PVDatabase::readCommands() {
    std::string inputCommand;

    while (true) {
        std::cout << "Command: ";
        getline(std::cin, inputCommand);
        try {
            CommandInterpreter::execute(inputCommand, *(this->pH), *(this->vH));
        }
        catch (const EndException& e) {
            std::cout << e.what() << std::endl;
            break;
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}
