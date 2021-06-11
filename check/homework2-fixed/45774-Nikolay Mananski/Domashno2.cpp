#include <iostream>
#include <string>
#include <vector>

#include "Command.h"
#include "Vehicle.h"
#include "Person.h"
#include "Registration.h"

const char* Registration::getRegNum() const
{
    return regNum.c_str();
}

const char* Vehicle::registration() const {
    return regNum.getRegNum();
}

const std::vector<Vehicle*> Vehicles::find(const char* registration) const {
    size_t br = 0;
    bool isFound = false;
    const char* regArr;
    while (!isFound && br < numCars)
    {
        regArr = (*vehicles[br])->registration();
        /*registration uses c_str which allocates dynamic memory and has to be deleted*/
        isFound = (strcmp(regArr, registration) == 0);
        delete[] regArr;
        br++;
    }
    if (!isFound) //no such vehicle
    {
        return {};
    }

    return vehicles[br - 1];
}

Registration::Registration(std::string regNumber)
{
    if (isValidRegNum(regNumber))
    {
        this->regNum = regNum;
    }
    else
    {
        throw std::exception("The registration number is not valid!\n");
    }
}

bool Registration::isValidRegNum(std::string regNumber)
{
    int i = 0;
    int placeSym = 0;
    int nums = 0;
    int symbols = 0;

    while (std::isalpha(regNumber[i]))
    {
        ++placeSym;
        ++i;
    }

    while (std::isdigit(regNumber[i]))
    {
        ++nums;
        ++i;
    }

    while (std::isalpha(regNumber[i]))
    {
        ++symbols;
        ++i;
    }

    if ((placeSym >= 1 && placeSym <= 2) && (nums == 4) && (symbols == 2))
    {
        return true;
    }

    return false;
}

Vehicle::Vehicle(Registration regNumber, std::string description)
    :regNum(regNumber)
{
    this->description = description;
}

bool Vehicle::setOwner(Person owner)
{
    this->owner = owner;
    return true;
}

Command::Command(std::string commandName, std::string arguments)
{
    this->commandName = commandName;
    this->arg = arguments;
}

std::string Command::getCommandName(Command& command)
{
    return command.commandName;
}

std::string Command::getArg(Command& command)
{
    return command.arg;
}


int main()
{
    std::string str;
    std::getline(std::cin, str);
    std::string command;
    std::string args;

    
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            command = str.substr(0, i);
            args = str.substr(i);
            break;
        }
    }

    /*std::transform(command.begin(), command.end(), command.begin(), ::tolower);*/

    for (size_t i = 0; i < command.length(); i++)
    {
        ::tolower(command[i]);
    }
    Command command(command, args);

    if (command == "regisration")
    {
        std::string registration;
        std::string description;
        for (size_t i = 0; i < args.length(); i++)
        {
            if (str[i] == ' ')
            {
                registration = str.substr(0, i);
                description = str.substr(i);
                break;
            }
        }

    }

    /*std::string str;
    std::getline(std::cin, str);
    std::string delimiter = " ";
    
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);

        if (token == "VEHICLE")
        {

        }

        str.erase(0, pos + delimiter.length());
    }
    std::cout << str << std::endl;*/

    /*
    do {
        std::cin >> command;
        std::string segment;
        while (std::getline(command, segment, ' '))
        {

        }

    } while ("EXIT" != command);*/

    

    return 0;
}
