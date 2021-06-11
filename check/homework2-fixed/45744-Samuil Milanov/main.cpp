#include <iostream>
#include "Person.h"
#include "Commands.h"
#include <string>
#include <cstring>

class Vehicle;
class Person;

int main() {
    std::cout << "Do you wish to load a file beforehand? Type 'yes' to load.\n";
    std::string command;
    std::cin >> command;
    UpperToLower(command);
    std::vector<Vehicle> VehicleList;
    std::vector<Person> PersonList;
    if(strcmp(command.c_str(), "yes") == 0)
    {
        std::string path;
        std::cout <<  "Enter Path:\n";
        std::cin >> path;
        LoadFromFile(path, PersonList, VehicleList);
    }
    std::cout << "Commands:\n";
    std::cout <<  "1. person\n";
    std::cout <<  "2. vehicle\n";
    std::cout <<  "3. acquire\n";
    std::cout <<  "4. release\n";
    std::cout <<  "5. remove\n";
    std::cout <<  "6. save\n";
    std::cout <<  "6. show\n";

    while(std::strcmp(command.c_str(), "exit") != 0) {
        std::cout << "Enter command\n";
        std::cin >> command;
        UpperToLower(command);
        if (std::strcmp(command.c_str(), "person") == 0) {
            try {
                std::cout << "Enter a name:\n";
                std::string name;
                std::getline(std::cin >> std::ws, name);
                std::cout << "Enter a id:\n";
                unsigned int id;
                if(std::cin >> id)
                {
                    CreatePerson(PersonList, id, name);
                }
                else
                {
                    std::cout << "Not a valid id, it must be a positive integer!" << std::endl;
                    std::cin.ignore();
                    std::cin.clear();
                }
            }
            catch(const char* message)
            {
                std::cout << message;
            }
        }
        if (std::strcmp(command.c_str(), "vehicle") == 0) {
            try {
                std::cout << "Enter a registration number:\n";
                std::string reg;
                std::cin >> reg;
                if(!IsValidReg(reg)) {
                    throw "Not a valid Registration!";
                }
                Registration registr(reg);
                std::cout << "Enter a description:\n";
                std::string descr;
                std::getline(std::cin >> std::ws, descr);
                CreateVehicle(VehicleList, descr, registr);
            }
            catch (const char* message)
            {
                std::cout << message << std::endl;
            }
        }
        if (std::strcmp(command.c_str(), "acquire") == 0) {
            try {
                std::cout << "Enter reg number:\n";
                std::string reg;
                std::cin >> reg;
                if (IsValidReg(reg) == 1) {
                    try {
                        std::cout << "Enter id:\n";
                        unsigned int id;
                        if(std::cin >> id)
                        {
                            ACQUIRE(reg, id, PersonList, VehicleList);
                        }
                        else
                        {
                            std::cout << "Not a valid id, it must be a positive integer!" << std::endl;
                            std::cin.ignore();
                            std::cin.clear();
                        }
                    }
                    catch (const char *message) {
                        std::cout << message << std::endl;
                    }
                } else {
                    throw "Not a valid Registration\n";
                }
            }
            catch(const char* message)
            {
                std::cout << message << std::endl;
            }

        }
        if (std::strcmp(command.c_str(), "release") == 0) {
            try {
                std::string reg;
                std::cout << "Registration number:\n";
                std::cin >> reg;
                unsigned int id;
                std::cout << "Id:\n ";
                if(std::cin >> id)
                {
                    if (IsValidReg(reg)) {
                        RELEASE(reg, id, PersonList, VehicleList);
                    }
                    else
                    {
                        throw "This is not a valid registration number!\n";
                    }
                }
                else
                {
                    std::cout << "Not a valid id, it must be a positive integer!" << std::endl;
                    std::cin.ignore();
                    std::cin.clear();
                }
            }
            catch(const char* message)
            {
                std::cout << message << std::endl;
            }

        }
        if (std::strcmp(command.c_str(), "remove") == 0) {
            std::string command2;
            std::cout << "Enter Id or Registration number:\n";
            std::cin >> command2;
            if(RegOrId(command2) == 1) {
                try {
                REMOVEVeh(command2, VehicleList, PersonList);
                }
                catch (const char* message)
                {
                    std::cout << message;
                }
            }
            if(RegOrId(command2) == 2)
            {
                unsigned int ident = 0;
                for (int i = 0; i < command2.size(); i++) {
                    ident = ident + (command2.at(i) - '0') * pow(10, command2.size() - i - 1);
                }
                try{
                    RemovePerson(ident, PersonList, VehicleList);
                }
                catch (const char* message)
                {
                    std::cout << message;
                }
            }
            if(RegOrId(command2) == 0)
            {
                std::cout << "Not a valid Id or Registration Number!\n";
            }
        }
        if (std::strcmp(command.c_str(), "show") == 0) {
            std::string command3;
            std::cout << "Enter Id or Registration number:\n";
            std::cin >> command3;
            if(RegOrId(command3) == 1)
            {
                try {
                    SHOWVehicleWithPerson(command3, VehicleList);
                }
                catch(...)
                {
                    std::cout << "An Error occurred\n;";
                }
            }
            else if(RegOrId(command3) == 2)
            {
                unsigned int ident = 0;
                for (int i = 0; i < command3.size(); i++) {
                    ident = ident + (command3.at(i) - '0') * pow(10, command3.size() - i - 1);
                }
                SHOWVPersonWithVehicle(ident, PersonList);
            }
            else
            {
                UpperToLower(command3);
                if(strcmp(command3.c_str(), "person") == 0)
                {
                    SHOWPeople(PersonList);
                }
                else if(strcmp(command3.c_str(), "vehicle") == 0)
                {
                    SHOWVehicles(VehicleList);
                }
                else std::cout << "Not a valid Id, Registration number, or command!\n";
            }
        }
        if (std::strcmp(command.c_str(), "save") == 0) {
            std::string path;
            std::cout<< "Enter path:\n";
            std::cin >> path;
            SAVE(path, PersonList, VehicleList);
        }
    }
    return 0;
}
