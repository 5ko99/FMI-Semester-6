#include <iostream>
#include <fstream>
#include "Headers/Command.h"
#include "Headers/Vehicle.h"
#include "Headers/Person.h"
#include "Headers/DataBase.h"
void error(){
    std::cout << "Please try again\n";
}

int main(int argc, char *argv[]) {
    std::string command;
//    std::cout << "Welcome to Homework2 Yani Drenchev 45518" << "\n";
//    std::cout << "List of available commands : " << "\n";
//    printAllCommands();
    std::string filename;
    if (argc > 1){
        filename = argv[1];
        DataBase::get_instance().importFromFile(filename);
    }else{
        std::cout << "Starting with empty DataBase" << "\n";
    }
    while (true) {
        std::getline(std::cin, command);
        auto x = parseCommand(command);
        while(x.first == CommandCode::NIL){
            error();
            std::getline(std::cin, command);
            x = parseCommand(command);
        }

        if(x.first == CommandCode::EXIT){
            std::cout << "Aufwiedersehen";
            return 1;
        }

        bool isSuccess = DataBase::get_instance().executeCommand(x, command);
        while (!isSuccess){
            error();
            std::getline(std::cin, command);
            x = parseCommand(command);
            isSuccess = DataBase::get_instance().executeCommand(x, command);
        }
    }

}
