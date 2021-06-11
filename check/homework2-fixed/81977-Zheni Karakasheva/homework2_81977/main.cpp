#include <iostream>
#include <fstream>
#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"
#include "DataBase.h"

//to compile: g++ main.cpp Registration.cpp Vehicle.cpp Person.cpp DataBase.cpp

//main takes two arguments to make sure we can execute the database by the model "program.exe "C:\Temp\My Program\Info.txt" "
int main(int argumentOne, char* argumentTwo[]) {
    std::vector<Registration*> registrations;
    std::vector<Person*> people;
    std::vector<Vehicle*> vehicles;

    DataBase dataBase(registrations, vehicles, people);

    if (argumentOne < 2) {
        std::cout<<"Insert a command or type X for exit: "<<std::endl;
        std::string command;

        while (1) {
            getline(std::cin, command);

            if (command == "X" || command == "x") { 
                break; 
            } 
            
            if(command.length()) {
                try {
                    dataBase.run(command);
                } catch(const std::invalid_argument& invalidCommand) {
                    std::cout<<invalidCommand.what()<<std::endl;
                }
            }

        }
    } else {
        std::ifstream fileToRead(argumentTwo[1], std::ios::in);
        std::string commandLine;
        for (commandLine; getline(fileToRead, commandLine);) {
            std::cout<<commandLine<<std::endl;
            dataBase.run(commandLine);
        }

        fileToRead.close();
    }

    return 0;
}
