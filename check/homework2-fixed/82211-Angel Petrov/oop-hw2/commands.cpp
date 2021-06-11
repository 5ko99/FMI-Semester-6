#include <iostream>
#include "registration.h"
#include "commands.h"

Commands* Commands::instance = 0;

// accessor for instance
Commands* Commands::getInstance() { 

    if(!instance) {
        instance = new Commands;
    }

    return instance;
}

Commands::Commands() {

    command = "N/A";
    firstArg = "N/A";
    secondArg = "N/A";
} 

void Commands::casePerson(std::string userInput, size_t& i) {

    // if the name has quotes in it skips them and extracts the name itself
    if (userInput[i] != '"') {
        for(; userInput[i] != ' '; ++i) {

            firstArg.push_back(userInput[i]);
        }

        ++i; // skips the whitespace

        for(;i < userInput.size(); ++i) {

            secondArg.push_back(userInput[i]);
        }
    }
    // if the doesn't have quotes just extract the name
    else {
        ++i; //skips '"'

        for(; userInput[i] != '"'; ++i) {

            firstArg.push_back(userInput[i]);
        }

        i+=2; // skips '"' and ' '

        for(;i < userInput.size(); ++i) {

            secondArg.push_back(userInput[i]);
        }
    }
}

// if the command is acquire, release or vehicle we have 2 arguments
void Commands::caseAcquireReleaseVehicle(std::string userInput, size_t& i) {

    // extracts first arg
    for(; userInput[i] != ' '; ++i) {

        firstArg.push_back(userInput[i]);
    }    

    ++i; // skips whitespace

    // extracts second arg
    for(; i < userInput.size(); ++i) {
        
        secondArg.push_back(userInput[i]);
    }
}

// if the command is remove, save or show we have 1 argument
void Commands::caseRemoveSaveShow(std::string userInput, size_t& i) {

    // extracts first arg
    for(; i < userInput.size(); ++i) {

        firstArg.push_back(userInput[i]);
    }
}

// if the command is exit
bool Commands::isExit(std::string command) {

    this->command = argumentToCaps(command);
    std::string exit("EXIT");

    return this->command == exit;
}

// reads user's input and splits it into arguments and command
void Commands::readAndSplitInput() {

    std::string userInput;
    // reads
    std::getline(std::cin, userInput);
    
    std::size_t i = 0;

    // clears the default value
    command.clear();
    firstArg.clear();
    secondArg.clear();

    // extracts until first whitespace is found
    while(userInput[i] != ' ') {
        command.push_back(userInput[i]);
        
        // if the command is exit, exit
        if(i == 3 && isExit(command)) 
            return;
        ++i;
    }

    // makes the command all caps 
    command = argumentToCaps(command);

    // skips all whitespaces
    while(userInput[i] == ' ') {
        ++i;
    }

    // extracts the arguments in different cases
    if (command == "VEHICLE" || command == "ACQUIRE" || command == "RELEASE") {

        caseAcquireReleaseVehicle(userInput, i);
    }
    else if (command == "REMOVE" || command == "SHOW" || command == "SAVE") {

        caseRemoveSaveShow(userInput, i);
    }
    else  if (command == "PERSON" ) {
        casePerson(userInput, i);
    } 
    // if a wrong command is read, throw excp
    else {
        try {
            throw std::invalid_argument("Unrecognisable command.\n");
        }
        catch (std::invalid_argument& e) {
            std::cout << e.what();
        }
    }

}

// accessors
std::string Commands::getCommand() const {

    return command;
}

std::string Commands::getFirstArg() const {

    return firstArg;
}

std::string Commands::getSecondArg() const {

    return secondArg;
}

// converts str to Registration
Registration Commands::toRegistration(std::string arg) {

    return Registration(arg);
}

// converts arg to all caps
std::string Commands::argumentToCaps(std::string arg) {

    for (size_t i = 0; i < arg.size(); ++i) {
        if (arg[i] >= 'a' && arg[i] <= 'z') {
            arg[i] = arg[i] - 'a' + 'A';
        }
    }

    return arg;
}
